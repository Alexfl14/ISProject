#ifndef SOKOBANGAME_GUI_VIEW_H
#define SOKOBANGAME_GUI_VIEW_H

#include <interfaces/IGame.h>
#include <interfaces/IGameObserver.h>
#include <enums/EGameEvent.h>
#include <raylib.h>
#include <string>

class GUI_View : public IGameObserver {
public:
    explicit GUI_View(IGame* game);
    ~GUI_View();
    
    void initialize(int screenWidth, int screenHeight);
    
    void onNotify(EGameEvent event) override;
    
    void render();
    
    void handleInput();
    
    bool shouldClose() const;
    
    void cleanup();

private:
    IGame* _gameLogic;

    int _screenWidth;
    int _screenHeight;
    int _tileSize;
    
    int _offsetX;
    int _offsetY;
    
    Color _wallColor;
    Color _floorColor;
    Color _targetColor;
    Color _boxColor;
    Color _boxOnTargetColor;
    Color _playerColor;

    Texture2D _carTexture;
    Texture2D _parkingTexture;

    std::string _statusMessage;
    bool _isInitialized;
    int _currentLevel;
    
    void drawTile(int row, int col, ETileType tileType);
    void drawPlayer(Position playerPos);
    void drawBox(Position boxPos, bool onTarget);
    void drawUI();
    void calculateOffsets();
    void loadNextLevel();
    Vector2 getTileScreenPosition(int row, int col) const;
};

#endif