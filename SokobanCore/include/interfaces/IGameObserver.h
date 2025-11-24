//

#ifndef SOKOBANGAME_IGAMEOBSERVER_H
#define SOKOBANGAME_IGAMEOBSERVER_H
#include "enums/EGameEvent.h"

class IGameObserver {
public:
    virtual ~IGameObserver() = default;
    virtual void onNotify(EGameEvent event) = 0;
};

#endif
