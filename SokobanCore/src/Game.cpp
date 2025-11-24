#include "Game.h"
#include <algorithm>

Game::Game() : _player(Position(0, 0)), _moveCount(0), _currentLevel(0), _gameState(EGameState::LOADING) {}

void Game::loadLevel(int levelNumber) {
    _gameState = EGameState::LOADING;
    _currentLevel = levelNumber;
    _currentMap.load(levelNumber);
    _player.setPosition(_currentMap.getPlayerStart());
    _boxes.clear();
    std::vector<Position> boxPositions = _currentMap.getBoxPositions();
    for (const auto& pos : boxPositions) {
        _boxes.emplace_back(pos);
    }
    
    _moveCount = 0;
    _gameState = EGameState::PLAYING;
    
    notify(EGameEvent::LEVEL_RELOADED);
}

void Game::movePlayer(EFacing direction) {
    if (_gameState != EGameState::PLAYING) {
        return;
    }
    
    Position currentPos = _player.getPosition();
    Position nextPos = getNextPosition(currentPos, direction);
    if (!isPositionWalkable(nextPos)) {
        return;
    }
    if (isBoxAt(nextPos)) {
        Position boxNextPos = getNextPosition(nextPos, direction);
        if (!isPositionWalkable(boxNextPos) || isBoxAt(boxNextPos)) {
            return;
        }
        Box* box = getBoxAt(nextPos);
        if (box) {
            box->setPosition(boxNextPos);
            notify(EGameEvent::BOX_MOVED);
        }
    }
    _player.setPosition(nextPos);
    _moveCount++;
    notify(EGameEvent::PLAYER_MOVED);
    if (checkWinCondition()) {
        _gameState = EGameState::LEVEL_COMPLETED;
        notify(EGameEvent::LEVEL_WON);
    }
}

void Game::restartLevel() {
    loadLevel(_currentLevel);
}

void Game::addObserver(IGameObserver *observer) {
    if (observer) {
        _observers.push_back(observer);
    }
}

void Game::removeObserver(IGameObserver *observer) {
    auto it = std::find(_observers.begin(), _observers.end(), observer);
    if (it != _observers.end()) {
        _observers.erase(it);
    }
}

void Game::notify(EGameEvent event) {
    for (auto* observer : _observers) {
        if (observer) {
            observer->onNotify(event);
        }
    }
}

bool Game::checkWinCondition() {
    for (const auto& box : _boxes) {
        Position boxPos = box.getPosition();
        ETileType tile = _currentMap.getTileAt(boxPos.getRow(), boxPos.getCol());
        
        if (tile != ETileType::TARGET) {
            return false;
        }
    }
    return true;
}

EGameState Game::getCurrentState() {
    return _gameState;
}

int Game::getLevelWidth() {
    return _currentMap.getWidth();
}

int Game::getLevelLength() {
    return _currentMap.getHeight();
}

ETileType Game::getTileAt(Position position) {
    return _currentMap.getTileAt(position.getRow(), position.getCol());
}

Position Game::getPlayerPosition() {
    return _player.getPosition();
}

const std::vector<Position>& Game::getBoxPositions() {
    static std::vector<Position> positions;
    positions.clear();
    
    for (const auto& box : _boxes) {
        positions.push_back(box.getPosition());
    }
    
    return positions;
}

int Game::getMoveCount() {
    return _moveCount;
}

bool Game::isPositionWalkable(const Position& pos) const {
    int row = pos.getRow();
    int col = pos.getCol();
    if (row < 0 || row >= _currentMap.getHeight() || 
        col < 0 || col >= _currentMap.getWidth()) {
        return false;
    }
    ETileType tile = _currentMap.getTileAt(row, col);
    return tile != ETileType::WALL;
}

bool Game::isBoxAt(const Position& pos) const {
    for (const auto& box : _boxes) {
        if (box.getPosition() == pos) {
            return true;
        }
    }
    return false;
}

Box* Game::getBoxAt(const Position& pos) {
    for (auto& box : _boxes) {
        if (box.getPosition() == pos) {
            return &box;
        }
    }
    return nullptr;
}

Position Game::getNextPosition(const Position& current, EFacing direction) const {
    int newRow = current.getRow();
    int newCol = current.getCol();
    
    switch (direction) {
        case EFacing::UP:
            newRow--;
            break;
        case EFacing::DOWN:
            newRow++;
            break;
        case EFacing::LEFT:
            newCol--;
            break;
        case EFacing::RIGHT:
            newCol++;
            break;
    }
    
    return Position(newRow, newCol);
}
