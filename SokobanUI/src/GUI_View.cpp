//
// Created by fafa on 12.11.2025.
//

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
    // Define colors matching the Sokoban image
    _wallColor = Color{100, 100, 100, 255};        // Gray stone walls
    _floorColor = Color{220, 200, 150, 255};       // Sand/beige floor
    _targetColor = Color{255, 150, 150, 255};      // Pink target circles
    _boxColor = Color{255, 165, 0, 255};           // Orange boxes
    _boxOnTargetColor = Color{200, 100, 0, 255};   // Dark orange for box on target
    _playerColor = Color{70, 130, 180, 255};       // Blue player
}

GUI_View::~GUI_View() {
    cleanup();
}

void GUI_View::initialize(int screenWidth, int screenHeight) {
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    
    InitWindow(_screenWidth, _screenHeight, "Sokoban Game - Observer Pattern Demo");
    SetTargetFPS(60);

    // --- LOAD ASSETS HERE (Must be done AFTER InitWindow) ---
    _carTexture = LoadTexture("assets/car.png");
    _parkingTexture = LoadTexture("assets/parking_spot.png");

    // Simple error check
    if (_carTexture.id == 0) std::cout << "WARNING: assets/car.png not found" << std::endl;
    if (_parkingTexture.id == 0) std::cout << "WARNING: assets/parking_spot.png not found" << std::endl;

    if (_gameLogic) {
        int mapWidth = _gameLogic->getLevelWidth();
        int mapHeight = _gameLogic->getLevelLength();

        // Calculate optimal tile size to fit the screen
        int maxTileWidth = (_screenWidth - 100) / mapWidth;
        int maxTileHeight = (_screenHeight - 150) / mapHeight;
        _tileSize = std::min(maxTileWidth, maxTileHeight);
        _tileSize = std::max(32, std::min(_tileSize, 64)); // Clamp between 32-64

        calculateOffsets();
    }

    _isInitialized = true;
    std::cout << "GUI_View initialized as Observer\n";
}

void GUI_View::cleanup() {
    if (_isInitialized && IsWindowReady()) {
        // --- UNLOAD ASSETS ---
        UnloadTexture(_carTexture);
        UnloadTexture(_parkingTexture);

        CloseWindow();
        _isInitialized = false;
        std::cout << "GUI_View cleaned up\n";
    }
}

/**
 * Observer Pattern - This method is called by the Subject (Game)
 * when game state changes
 */
void GUI_View::onNotify(EGameEvent event) {
    switch(event) {
        case EGameEvent::LEVEL_WON:
            _statusMessage = "Level Complete! Press N for next level or R to restart.";
            std::cout << "Observer notified: LEVEL_WON\n";
            break;

        case EGameEvent::LEVEL_RELOADED:
            _statusMessage = "Level Loaded! Use Arrow Keys to move.";
            calculateOffsets(); // Recalculate for new level
            std::cout << "Observer notified: LEVEL_RELOADED\n";
            break;

        case EGameEvent::PLAYER_MOVED:
            // Update move counter display
            break;

        case EGameEvent::BOX_MOVED:
            // Could add sound effect here
            break;
    }
}

void GUI_View::render() {
    if (!_isInitialized || !_gameLogic) {
        return;
    }

    BeginDrawing();
    ClearBackground(Color{50, 50, 50, 255}); // Dark gray background

    int mapWidth = _gameLogic->getLevelWidth();
    int mapHeight = _gameLogic->getLevelLength();

    // Draw all tiles (walls, floors, targets)
    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            Position pos(row, col);
            ETileType tileType = _gameLogic->getTileAt(pos);
            drawTile(row, col, tileType);
        }
    }

    // Draw all boxes
    auto boxPositions = _gameLogic->getBoxPositions();
    for (const auto& boxPos : boxPositions) {
        ETileType tileType = _gameLogic->getTileAt(boxPos);
        bool onTarget = (tileType == ETileType::TARGET);
        drawBox(boxPos, onTarget);
    }

    // Draw player
    Position playerPos = _gameLogic->getPlayerPosition();
    drawPlayer(playerPos);

    // Draw UI (status bar, move counter)
    drawUI();

    EndDrawing();
}

void GUI_View::drawTile(int row, int col, ETileType tileType) {
    Vector2 screenPos = getTileScreenPosition(row, col);
    Rectangle tileRect = {screenPos.x, screenPos.y, (float)_tileSize, (float)_tileSize};

    // Helper variables for drawing textures
    Vector2 origin = {0,0};

    switch(tileType) {
        case ETileType::WALL:
            // Draw stone wall texture (kept procedural as per previous code,
            // but you can replace this with a texture if you have one)
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
            // Draw floor
            DrawRectangleRec(tileRect, _floorColor);
            DrawRectangleLinesEx(tileRect, 1, Color{200, 180, 130, 255});
            break;

        case ETileType::TARGET:
            // 1. Draw floor background first (so transparency works)
            DrawRectangleRec(tileRect, _floorColor);

            // 2. Draw Parking Spot Texture
            if (_parkingTexture.id != 0) {
                Rectangle sourceRec = { 0.0f, 0.0f, (float)_parkingTexture.width, (float)_parkingTexture.height };
                DrawTexturePro(_parkingTexture, sourceRec, tileRect, origin, 0.0f, WHITE);
            } else {
                // Fallback if texture failed to load
                Vector2 center = {screenPos.x + _tileSize/2.0f, screenPos.y + _tileSize/2.0f};
                DrawCircle(center.x, center.y, _tileSize/3.0f, _targetColor);
            }

            // Optional: keep the border
            DrawRectangleLinesEx(tileRect, 1, Color{200, 180, 130, 255});
            break;
    }
}

void GUI_View::drawPlayer(Position playerPos) {
    // Kept the same as your original code
    Vector2 screenPos = getTileScreenPosition(playerPos.getRow(), playerPos.getCol());
    Vector2 center = {screenPos.x + _tileSize/2.0f, screenPos.y + _tileSize/2.0f};

    float playerSize = _tileSize * 0.6f;

    // Draw simple character (body)
    DrawCircle(center.x, center.y + playerSize/6, playerSize/3, _playerColor);

    // Draw head
    DrawCircle(center.x, center.y - playerSize/4, playerSize/4, /*Color{255, 220, 180, 255}*/ BROWN);

    // Draw eyes
    DrawCircle(center.x - playerSize/10, center.y - playerSize/4 - 2, 2, BLACK);
    DrawCircle(center.x + playerSize/10, center.y - playerSize/4 - 2, 2, BLACK);

    // Draw legs
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

    // 1. Draw floor underneath (important if car has transparent windows)
    DrawRectangleRec(boxRect, _floorColor);

    // 2. Draw Car Texture
    if (_carTexture.id != 0) {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)_carTexture.width, (float)_carTexture.height };
        Vector2 origin = { 0.0f, 0.0f };

        // If on target, we draw it normally (the logic is: visually the car is parked on the spot)
        // If you want to tint it when parked, change WHITE to GREEN
        Color tint = onTarget ? GREEN : WHITE;

        DrawTexturePro(_carTexture, sourceRec, boxRect, origin, 0.0f, WHITE);
    }
    else {
        // Fallback to original rectangle logic
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
    // Top status bar
    DrawRectangle(0, 0, _screenWidth, 40, Color{30, 30, 30, 255});

    // Level indicator
    std::string levelText = "Level: " + std::to_string(_currentLevel) + "/10";
    DrawText(levelText.c_str(), 10, 10, 20, BLUE);

    // Move counter
    int moveCount = _gameLogic->getMoveCount();
    std::string movesText = "Moves: " + std::to_string(moveCount);
    DrawText(movesText.c_str(), 150, 10, 20, WHITE);

    // Status message
    DrawText(_statusMessage.c_str(), 300, 10, 20, YELLOW);

    // Bottom instruction bar
    DrawRectangle(0, _screenHeight - 40, _screenWidth, 40, Color{30, 30, 30, 255});
    DrawText("Arrow/WASD: Move | R: Restart | N: Next Level | ESC: Exit", 10, _screenHeight - 30, 20, LIGHTGRAY);
}

void GUI_View::handleInput() {
    if (!_gameLogic) return;

    // Movement controls
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

    // Restart level
    if (IsKeyPressed(KEY_R)) {
        _gameLogic->restartLevel();
    }

    // Next level
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
    _offsetY = (_screenHeight - totalHeight) / 2 + 20; // +20 for top bar
}

void GUI_View::loadNextLevel() {
    if (!_gameLogic) return;
    
    // Increment level (max 10 levels)
    _currentLevel++;
    
    if (_currentLevel > 10) {
        _currentLevel = 10;
        _statusMessage = "You've completed all levels! Congratulations!";
        std::cout << "All levels completed!\n";
        return;
    }
    
    try {
        _gameLogic->loadLevel(_currentLevel);
        
        // Recalculate tile size and offsets for new level
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
        _currentLevel--; // Revert on error
    }
}

Vector2 GUI_View::getTileScreenPosition(int row, int col) const {
    return Vector2{
        (float)(_offsetX + col * _tileSize),
        (float)(_offsetY + row * _tileSize)
    };
}