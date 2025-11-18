//
// Created by fafa on 12.11.2025.
//

#ifndef ISPROJECT_GAMEMAP_H
#define ISPROJECT_GAMEMAP_H
#include <vector>
#include "Tile.h"
#include "Position.h"
#include "interfaces/IGameMap.h"

class GameMap: public IGameMap{
public:
    GameMap();
    void load(int levelNumber) override;
    
    int getWidth() const;
    int getHeight() const;
    ETileType getTileAt(int row, int col) const;
    Position getPlayerStart() const;
    std::vector<Position> getBoxPositions() const;
    
private:
    std::vector<std::vector<Tile>> _grid;
    Position _playerStart;
    std::vector<Position> _boxPositions;
    int _width;
    int _height;
};

#endif //ISPROJECT_GAMEMAP_H
