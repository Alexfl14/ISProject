#include "Game.h"
#include <algorithm>

Game::Game() : _player(Position(0, 0)), _moveCount(0), _currentLevel(0), _gameState(EGameState::LOADING) {}

void Game::loadLevel(int levelNumber) {
    _gameState = EGameState::LOADING;
    _currentLevel = levelNumber;
    
    // Load map from JSON
    _currentMap.load(levelNumber);
    
    // Initialize player
    _player.setPosition(_currentMap.getPlayerStart());
    
    // Initialize boxes
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
    
    // Check if next position is walkable
    if (!isPositionWalkable(nextPos)) {
        return; // Can't move into wall
    }
    
    // Check if there's a box at next position
    if (isBoxAt(nextPos)) {
        // Try to push the box
        Position boxNextPos = getNextPosition(nextPos, direction);
        
        // Check if box can be pushed
        if (!isPositionWalkable(boxNextPos) || isBoxAt(boxNextPos)) {
            return; // Can't push box
        }
        
        // Move the box
        Box* box = getBoxAt(nextPos);
        if (box) {
            box->setPosition(boxNextPos);
            notify(EGameEvent::BOX_MOVED);
        }
    }
    
    // Move player
    _player.setPosition(nextPos);
    _moveCount++;
    notify(EGameEvent::PLAYER_MOVED);
    
    // Check win condition
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
    // All boxes must be on target tiles
    for (const auto& box : _boxes) {
        Position boxPos = box.getPosition();
        ETileType tile = _currentMap.getTileAt(boxPos.getRow(), boxPos.getCol());
        
        if (tile != ETileType::TARGET) {
            return false; // Box not on target
        }
    }
    return true; // All boxes on targets
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

// Private helper methods

bool Game::isPositionWalkable(const Position& pos) const {
    int row = pos.getRow();
    int col = pos.getCol();
    
    // Check bounds
    if (row < 0 || row >= _currentMap.getHeight() || 
        col < 0 || col >= _currentMap.getWidth()) {
        return false;
    }
    
    // Check if it's not a wall
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
