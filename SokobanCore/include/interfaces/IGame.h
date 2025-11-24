//

#ifndef ISPROJECT_IGAME_H
#define ISPROJECT_IGAME_H
#include "Position.h"
#include "enums/EFacing.h"
#include "enums/EGameState.h"
#include "enums/ETileType.h"
#include <vector>

#include "IGameSubject.h"

class IGame : public IGameSubject{
public:
    virtual ~IGame() = default;
    virtual void loadLevel(int levelNumber) = 0;
    virtual void movePlayer(EFacing direction) = 0;
    virtual void restartLevel() = 0;
    virtual EGameState getCurrentState() = 0;
    virtual int getLevelWidth() = 0;
    virtual int getLevelLength() = 0;
    virtual ETileType getTileAt(Position position) = 0;
    virtual Position getPlayerPosition() = 0;
    virtual const std::vector<Position>& getBoxPositions() = 0;
    virtual int getMoveCount() = 0;
};

#endif
