//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_IGAMEOBSERVER_H
#define SOKOBANGAME_IGAMEOBSERVER_H
#include "Enums/EGameEvent.h"

class IGameObserver {
public:
    virtual void onNotify(EGameEvent event);
};
#endif //SOKOBANGAME_IGAMEOBSERVER_H