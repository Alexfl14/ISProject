//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_IGAMEOBJECT_H
#define SOKOBANGAME_IGAMEOBJECT_H
class IGameObject {
public:
    virtual Position getPosition() const;
    virtual void setPosition(Position position);
};
#endif //SOKOBANGAME_IGAMEOBJECT_H