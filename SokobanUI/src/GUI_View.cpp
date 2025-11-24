#include "GUI_View.h"
#include <iostream>
#include <algorithm>

GUI_View::GUI_View(IGame* game) 
    : _gameLogic(game),
      _screenWidth(800),
      _screenHeight(600),
      _tileSize(48),
      _offsetX(0),
      _offsetY(0),
      _isInitialized(false),
      _currentLevel(1),
      _statusMessage("Use Arrow Keys to move. R to restart.")
{
    _wallColor = Color{100, 100, 100, 255};
    _floorColor = Color{220, 200, 150, 255};
    _targetColor = Color{255, 150, 150, 255};
    _boxColor = Color{255, 165, 0, 255};
    _boxOnTargetColor = Color{200, 100, 0, 255};
    _playerColor = Color{70, 130, 180, 255};
}

GUI_View::~GUI_View() {
    cleanup();
}

void GUI_View::initialize(int screenWidth, int screenHeight) {
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    
    InitWindow(_screenWidth, _screenHeight, "Sokoban Game - Observer Pattern Demo");
    SetTargetFPS(60);

    _carTexture = LoadTexture("assets/car.png");
    _parkingTexture = LoadTexture("assets/parking_spot.png");

    if (_carTexture.id == 0) std::cout << "WARNING: assets/car.png not found" << std::endl;
    if (_parkingTexture.id == 0) std::cout << "WARNING: assets/parking_spot.png not found" << std::endl;

    if (_gameLogic) {
        int mapWidth = _gameLogic->getLevelWidth();
        int mapHeight = _gameLogic->getLevelLength();

        int maxTileWidth = (_screenWidth - 100) / mapWidth;
        int maxTileHeight = (_screenHeight - 150) / mapHeight;
        _tileSize = std::min(maxTileWidth, maxTileHeight);
        _tileSize = std::max(32, std::min(_tileSize, 64));

        calculateOffsets();
    }

    _isInitialized = true;
    std::cout << "GUI_View initialized as Observer\n";
}

void GUI_View::cleanup() {
    if (_isInitialized && IsWindowReady()) {
        UnloadTexture(_carTexture);
        UnloadTexture(_parkingTexture);

        CloseWindow();
        _isInitialized = false;
        std::cout << "GUI_View cleaned up\n";
    }
}

void GUI_View::onNotify(EGameEvent event) {
    switch(event) {
        case EGameEvent::LEVEL_WON:
            _statusMessage = "Level Complete! Press N for next level or R to restart.";
            std::cout << "Observer notified: LEVEL_WON\n";
            break;

        case EGameEvent::LEVEL_RELOADED:
            _statusMessage = "Level Loaded! Use Arrow Keys to move.";
            calculateOffsets();
            std::cout << "Observer notified: LEVEL_RELOADED\n";
            break;

        case EGameEvent::PLAYER_MOVED:
            break;

        case EGameEvent::BOX_MOVED:
            break;
    }
}

void GUI_View::render() {
    if (!_isInitialized || !_gameLogic) {
        return;
    }

    BeginDrawing();
    ClearBackground(Color{50, 50, 50, 255});

    int mapWidth = _gameLogic->getLevelWidth();
    int mapHeight = _gameLogic->getLevelLength();

    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            Position pos(row, col);
            ETileType tileType = _gameLogic->getTileAt(pos);
            drawTile(row, col, tileType);
        }
    }

    auto boxPositions = _gameLogic->getBoxPositions();
    for (const auto& boxPos : boxPositions) {
        ETileType tileType = _gameLogic->getTileAt(boxPos);
        bool onTarget = (tileType == ETileType::TARGET);
        drawBox(boxPos, onTarget);
    }

    Position playerPos = _gameLogic->getPlayerPosition();
    drawPlayer(playerPos);

    drawUI();

    EndDrawing();
}

void GUI_View::drawTile(int row, int col, ETileType tileType) {
    Vector2 screenPos = getTileScreenPosition(row, col);
    Rectangle tileRect = {screenPos.x, screenPos.y, (float)_tileSize, (float)_tileSize};

    Vector2 origin = {0,0};

    switch(tileType) {
        case ETileType::WALL:
            DrawRectangleRec(tileRect, _wallColor);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int stoneSize = _tileSize / 4;
                    Rectangle stone = {
                        screenPos.x + (i * stoneSize * 1.1f) + 2,
                        screenPos.y + (j * stoneSize * 1.1f) + 2,
                        (float)stoneSize - 2,
                        (float)stoneSize - 2
                    };
                    DrawRectangleRec(stone, Color{80, 80, 80, 255});
                    DrawRectangleLinesEx(stone, 1, Color{60, 60, 60, 255});
                }
            }
            break;

        case ETileType::PATH:
            DrawRectangleRec(tileRect, _floorColor);
            DrawRectangleLinesEx(tileRect, 1, Color{200, 180, 130, 255});
            break;

        case ETileType::TARGET:
            DrawRectangleRec(tileRect, _floorColor);

            if (_parkingTexture.id != 0) {
                Rectangle sourceRec = { 0.0f, 0.0f, (float)_parkingTexture.width, (float)_parkingTexture.height };
                DrawTexturePro(_parkingTexture, sourceRec, tileRect, origin, 0.0f, WHITE);
            } else {
                Vector2 center = {screenPos.x + _tileSize/2.0f, screenPos.y + _tileSize/2.0f};
                DrawCircle(center.x, center.y, _tileSize/3.0f, _targetColor);
            }

            DrawRectangleLinesEx(tileRect, 1, Color{200, 180, 130, 255});
            break;
    }
}

void GUI_View::drawPlayer(Position playerPos) {
    Vector2 screenPos = getTileScreenPosition(playerPos.getRow(), playerPos.getCol());
    Vector2 center = {screenPos.x + _tileSize/2.0f, screenPos.y + _tileSize/2.0f};

    float playerSize = _tileSize * 0.6f;

    DrawCircle(center.x, center.y + playerSize/6, playerSize/3, _playerColor);

    DrawCircle(center.x, center.y - playerSize/4, playerSize/4, BROWN);

    DrawCircle(center.x - playerSize/10, center.y - playerSize/4 - 2, 2, BLACK);
    DrawCircle(center.x + playerSize/10, center.y - playerSize/4 - 2, 2, BLACK);

    DrawRectangle(center.x - playerSize/8, center.y + playerSize/3, playerSize/7, playerSize/4, _playerColor);
    DrawRectangle(center.x + playerSize/16, center.y + playerSize/3, playerSize/7, playerSize/4, _playerColor);
}

void GUI_View::drawBox(Position boxPos, bool onTarget) {
    Vector2 screenPos = getTileScreenPosition(boxPos.getRow(), boxPos.getCol());

    Rectangle boxRect = {
        screenPos.x,
        screenPos.y,
        (float)_tileSize,
        (float)_tileSize
    };

    DrawRectangleRec(boxRect, _floorColor);

    if (_carTexture.id != 0) {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)_carTexture.width, (float)_carTexture.height };
        Vector2 origin = { 0.0f, 0.0f };

        Color tint = onTarget ? GREEN : WHITE;

        DrawTexturePro(_carTexture, sourceRec, boxRect, origin, 0.0f, WHITE);
    }
    else {
        Color boxColor = onTarget ? _boxOnTargetColor : _boxColor;
        float boxPadding = _tileSize * 0.1f;
        Rectangle innerRect = {
             screenPos.x + boxPadding, screenPos.y + boxPadding,
             _tileSize - 2*boxPadding, _tileSize - 2*boxPadding
        };
        DrawRectangleRec(innerRect, boxColor);
        DrawRectangleLinesEx(innerRect, 2, Color{150, 80, 0, 255});
    }
}

void GUI_View::drawUI() {
    DrawRectangle(0, 0, _screenWidth, 40, Color{30, 30, 30, 255});

    std::string levelText = "Level: " + std::to_string(_currentLevel) + "/10";
    DrawText(levelText.c_str(), 10, 10, 20, BLUE);

    int moveCount = _gameLogic->getMoveCount();
    std::string movesText = "Moves: " + std::to_string(moveCount);
    DrawText(movesText.c_str(), 150, 10, 20, WHITE);

    DrawText(_statusMessage.c_str(), 300, 10, 20, YELLOW);

    DrawRectangle(0, _screenHeight - 40, _screenWidth, 40, Color{30, 30, 30, 255});
    DrawText("Arrow/WASD: Move | R: Restart | N: Next Level | ESC: Exit", 10, _screenHeight - 30, 20, LIGHTGRAY);
}

void GUI_View::handleInput() {
    if (!_gameLogic) return;

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        _gameLogic->movePlayer(EFacing::UP);
    }
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        _gameLogic->movePlayer(EFacing::DOWN);
    }
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        _gameLogic->movePlayer(EFacing::LEFT);
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        _gameLogic->movePlayer(EFacing::RIGHT);
    }

    if (IsKeyPressed(KEY_R)) {
        _gameLogic->restartLevel();
    }

    if (IsKeyPressed(KEY_N)) {
        loadNextLevel();
    }
}

bool GUI_View::shouldClose() const {
    return WindowShouldClose();
}

void GUI_View::calculateOffsets() {
    if (!_gameLogic) return;
    
    int mapWidth = _gameLogic->getLevelWidth();
    int mapHeight = _gameLogic->getLevelLength();
    
    int totalWidth = mapWidth * _tileSize;
    int totalHeight = mapHeight * _tileSize;
    
    _offsetX = (_screenWidth - totalWidth) / 2;
    _offsetY = (_screenHeight - totalHeight) / 2 + 20;
}

void GUI_View::loadNextLevel() {
    if (!_gameLogic) return;
    
    _currentLevel++;
    
    if (_currentLevel > 10) {
        _currentLevel = 10;
        _statusMessage = "You've completed all levels! Congratulations!";
        std::cout << "All levels completed!\n";
        return;
    }
    
    try {
        _gameLogic->loadLevel(_currentLevel);
        
        int mapWidth = _gameLogic->getLevelWidth();
        int mapHeight = _gameLogic->getLevelLength();
        
        int maxTileWidth = (_screenWidth - 100) / mapWidth;
        int maxTileHeight = (_screenHeight - 150) / mapHeight;
        _tileSize = std::min(maxTileWidth, maxTileHeight);
        _tileSize = std::max(32, std::min(_tileSize, 64));
        
        calculateOffsets();
        
        _statusMessage = "Level " + std::to_string(_currentLevel) + " loaded!";
        std::cout << "Loaded level " << _currentLevel << "\n";
        
    } catch (const std::exception& e) {
        _statusMessage = "Failed to load level " + std::to_string(_currentLevel);
        std::cerr << "Error loading level: " << e.what() << "\n";
        _currentLevel--;
    }
}

Vector2 GUI_View::getTileScreenPosition(int row, int col) const {
    return Vector2{
        (float)(_offsetX + col * _tileSize),
        (float)(_offsetY + row * _tileSize)
    };
}