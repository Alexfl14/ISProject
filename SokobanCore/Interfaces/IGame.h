//
// Created by fafa on 12.11.2025.
//

#ifndef ISPROJECT_IGAME_H
#define ISPROJECT_IGAME_H
#include "Game/Position.h"
#include "Enums/EFacing.h"
#include "Enums/EGameState.h"
#include "Enums/ETileType.h"
#include <vector>

#include "IGameSubject.h"

class IGame : public IGameSubject{
public:
    virtual void loadLevel(int levelNumber);
    virtual void movePlayer(EFacing direction);
    virtual void restartLevel();
    virtual EGameState getCurrentState();
    virtual int getLevelWidth();
    virtual int getLevelLength();
    virtual ETileType getTileAt(Position position);
    virtual Position getPlayerPosition();
    virtual const std::vector<Position>& getBoxPositions();
    virtual int getMoveCount();
};
#endif //ISPROJECT_IGAME_H