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
    
    switch(tileType) {
        case ETileType::WALL:
            // Draw stone wall texture
            DrawRectangleRec(tileRect, _wallColor);
            
            // Add stone pattern (3x3 grid of smaller stones)
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
            // Draw floor first
            DrawRectangleRec(tileRect, _floorColor);
            DrawRectangleLinesEx(tileRect, 1, Color{200, 180, 130, 255});
            
            // Draw target circle (pink)
            Vector2 center = {screenPos.x + _tileSize/2.0f, screenPos.y + _tileSize/2.0f};
            DrawCircle(center.x, center.y, _tileSize/3.0f, _targetColor);
            DrawCircleLines(center.x, center.y, _tileSize/3.0f, Color{255, 100, 100, 255});
            break;
    }
}

void GUI_View::drawPlayer(Position playerPos) {
    Vector2 screenPos = getTileScreenPosition(playerPos.getRow(), playerPos.getCol());
    Vector2 center = {screenPos.x + _tileSize/2.0f, screenPos.y + _tileSize/2.0f};
    
    float playerSize = _tileSize * 0.6f;
    
    // Draw simple character (body)
    DrawCircle(center.x, center.y + playerSize/6, playerSize/3, _playerColor);
    
    // Draw head
    DrawCircle(center.x, center.y - playerSize/4, playerSize/4, Color{255, 220, 180, 255});
    
    // Draw eyes
    DrawCircle(center.x - playerSize/10, center.y - playerSize/4 - 2, 2, BLACK);
    DrawCircle(center.x + playerSize/10, center.y - playerSize/4 - 2, 2, BLACK);
    
    // Draw legs
    DrawRectangle(center.x - playerSize/8, center.y + playerSize/3, playerSize/7, playerSize/4, _playerColor);
    DrawRectangle(center.x + playerSize/16, center.y + playerSize/3, playerSize/7, playerSize/4, _playerColor);
}

void GUI_View::drawBox(Position boxPos, bool onTarget) {
    Vector2 screenPos = getTileScreenPosition(boxPos.getRow(), boxPos.getCol());
    
    Color boxColor = onTarget ? _boxOnTargetColor : _boxColor;
    float boxPadding = _tileSize * 0.1f;
    Rectangle boxRect = {
        screenPos.x + boxPadding,
        screenPos.y + boxPadding,
        _tileSize - 2*boxPadding,
        _tileSize - 2*boxPadding
    };
    
    // Draw box
    DrawRectangleRec(boxRect, boxColor);
    DrawRectangleLinesEx(boxRect, 2, Color{150, 80, 0, 255});
    
    // Draw X pattern (as in the image)
    Vector2 center = {screenPos.x + _tileSize/2.0f, screenPos.y + _tileSize/2.0f};
    float crossSize = _tileSize * 0.4f;
    
    DrawLineEx(
        Vector2{center.x - crossSize/2, center.y - crossSize/2},
        Vector2{center.x + crossSize/2, center.y + crossSize/2},
        2, Color{120, 60, 0, 255}
    );
    DrawLineEx(
        Vector2{center.x + crossSize/2, center.y - crossSize/2},
        Vector2{center.x - crossSize/2, center.y + crossSize/2},
        2, Color{120, 60, 0, 255}
    );
}

void GUI_View::drawUI() {
    // Top status bar
    DrawRectangle(0, 0, _screenWidth, 40, Color{30, 30, 30, 255});
    
    // Move counter
    int moveCount = _gameLogic->getMoveCount();
    std::string movesText = "Moves: " + std::to_string(moveCount);
    DrawText(movesText.c_str(), 10, 10, 20, WHITE);
    
    // Status message
    DrawText(_statusMessage.c_str(), 200, 10, 20, YELLOW);
    
    // Bottom instruction bar
    DrawRectangle(0, _screenHeight - 40, _screenWidth, 40, Color{30, 30, 30, 255});
    DrawText("Arrow Keys: Move | R: Restart | ESC: Exit", 10, _screenHeight - 30, 20, LIGHTGRAY);
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
}

bool GUI_View::shouldClose() const {
    return WindowShouldClose();
}

void GUI_View::cleanup() {
    if (_isInitialized && IsWindowReady()) {
        CloseWindow();
        _isInitialized = false;
        std::cout << "GUI_View cleaned up\n";
    }
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

Vector2 GUI_View::getTileScreenPosition(int row, int col) const {
    return Vector2{
        (float)(_offsetX + col * _tileSize),
        (float)(_offsetY + row * _tileSize)
    };
}