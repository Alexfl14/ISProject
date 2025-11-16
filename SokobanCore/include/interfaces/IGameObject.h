//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_IGAMEOBJECT_H
#define SOKOBANGAME_IGAMEOBJECT_H

#include "Position.h"

class IGameObject {
public:
    virtual ~IGameObject() = default;
    virtual Position getPosition() const = 0;
    virtual void setPosition(Position position) = 0;
};

#endif //SOKOBANGAME_IGAMEOBJECT_H
