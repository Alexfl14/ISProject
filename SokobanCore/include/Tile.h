//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_TILE_H
#define SOKOBANGAME_TILE_H
#include "enums/ETileType.h"

struct Tile {
public:
    Tile() : _tileType(ETileType::PATH) {}
    Tile(const ETileType tileType): _tileType(tileType) {}

    ETileType getTileType() const { return _tileType; }
    void setTileType(ETileType tileType) { _tileType = tileType; }
protected:
    ETileType _tileType;
};

#endif //SOKOBANGAME_TILE_H
