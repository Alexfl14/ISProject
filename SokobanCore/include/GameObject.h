//
// Created by fafa on 12.11.2025.
//

#ifndef ISPROJECT_GAMEOBJECT_H
#define ISPROJECT_GAMEOBJECT_H

#include "Position.h"
#include "interfaces/IGameObject.h"

class GameObject: public IGameObject {
public:
    GameObject(const Position position): _position(position){}

    Position getPosition() const override;
    void setPosition(Position position) override;
protected:
    Position _position;
};


#endif //ISPROJECT_GAMEOBJECT_H