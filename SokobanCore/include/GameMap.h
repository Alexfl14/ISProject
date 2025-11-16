//
// Created by fafa on 12.11.2025.
//

#ifndef ISPROJECT_GAMEMAP_H
#define ISPROJECT_GAMEMAP_H
#include <vector>
#include "Tile.h"
#include "Position.h"
#include "Interfaces/IGameMap.h"
class GameMap: IGameMap{
public:
    void load(int levelNumber) override;
private:
    std::vector<std::vector<Tile>> _grid;
    Position _playerStart;
};


#endif //ISPROJECT_GAMEMAP_H