//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_BOX_H
#define SOKOBANGAME_BOX_H
#include "GameObject.h"

class Box : public GameObject{
public:
    Box() : GameObject(Position(0, 0)) {}
    Box(const Position& position) : GameObject(position) {}
};

#endif //SOKOBANGAME_BOX_H
