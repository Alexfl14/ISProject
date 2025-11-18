//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_GUI_VIEW_H
#define SOKOBANGAME_GUI_VIEW_H

#include <interfaces/IGame.h>
#include <interfaces/IGameObserver.h>
#include <enums/EGameEvent.h>
#include <raylib.h>
#include <string>

/**
 * GUI_View - Observer Pattern Implementation
 * Observes the Game (Subject) and updates the UI accordingly
 */
class GUI_View : public IGameObserver {
public:
    explicit GUI_View(IGame* game);
    ~GUI_View();
    
    // Initialize raylib window
    void initialize(int screenWidth, int screenHeight);
    
    // Observer Pattern - called by Subject (Game) when state changes
    void onNotify(EGameEvent event) override;
    
    // Main rendering function
    void render();
    
    // Handle keyboard input
    void handleInput();
    
    // Check if window should close
    bool shouldClose() const;
    
    // Cleanup resources
    void cleanup();

private:
    IGame* _gameLogic;  // Reference to the Subject (Game)
    
    // Window properties
    int _screenWidth;
    int _screenHeight;
    int _tileSize;
    
    // Grid offset for centering
    int _offsetX;
    int _offsetY;
    
    // Colors matching the image
    Color _wallColor;
    Color _floorColor;
    Color _targetColor;
    Color _boxColor;
    Color _boxOnTargetColor;
    Color _playerColor;

    // --- NEW TEXTURES ---
    Texture2D _carTexture;
    Texture2D _parkingTexture;

    // UI state
    std::string _statusMessage;
    bool _isInitialized;
    int _currentLevel;
    
    // Helper methods
    void drawTile(int row, int col, ETileType tileType);
    void drawPlayer(Position playerPos);
    void drawBox(Position boxPos, bool onTarget);
    void drawUI();
    void calculateOffsets();
    void loadNextLevel();
    Vector2 getTileScreenPosition(int row, int col) const;
};

#endif //SOKOBANGAME_GUI_VIEW_H