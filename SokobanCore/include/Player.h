#ifndef SOKOBANGAME_PLAYER_H
#define SOKOBANGAME_PLAYER_H
#include "GameObject.h"

class Player : public GameObject {
public:
    Player() : GameObject(Position(0, 0)) {}
    Player(const Position& position) : GameObject(position) {}
};

#endif //SOKOBANGAME_PLAYER_H
