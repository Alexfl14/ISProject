//
// Created by fafa on 12.11.2025.
//

#ifndef ISPROJECT_GAME_H
#define ISPROJECT_GAME_H
#include "interfaces/IGame.h"
#include "GameMap.h"
#include <vector>
#include "interfaces/IGameObserver.h"
#include "Box.h"
#include "Player.h"

class Game: public IGame{
public:
    Game();
    void loadLevel(int levelNumber) override;
    void movePlayer(EFacing direction) override;
    void restartLevel() override;
    void addObserver(IGameObserver *observer) override;
    void removeObserver(IGameObserver *observer) override;
    void notify(EGameEvent event) override;
    bool checkWinCondition();
    EGameState getCurrentState() override;
    int getLevelWidth() override;
    int getLevelLength() override;
    ETileType getTileAt(Position position) override;
    Position getPlayerPosition() override;
    const std::vector<Position> & getBoxPositions() override;
    int getMoveCount() override;
    
private:
    bool isPositionWalkable(const Position& pos) const;
    bool isBoxAt(const Position& pos) const;
    Box* getBoxAt(const Position& pos);
    Position getNextPosition(const Position& current, EFacing direction) const;
    
    std::vector<IGameObserver*> _observers;
    GameMap _currentMap;
    Player _player;
    std::vector<Box> _boxes;
    int _moveCount;
    int _currentLevel;
    EGameState _gameState;
};

#endif //ISPROJECT_GAME_H
