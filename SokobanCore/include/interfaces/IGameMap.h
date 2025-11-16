//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_IGAMEMAP_H
#define SOKOBANGAME_IGAMEMAP_H

class IGameMap {
public:
    virtual ~IGameMap() = default;
    virtual void load(int levelNumber) = 0;
};

#endif //SOKOBANGAME_IGAMEMAP_H
