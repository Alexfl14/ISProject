//
// Created by fafa on 12.11.2025.
//

#ifndef ISPROJECT_IGAMESUBJECT_H
#define ISPROJECT_IGAMESUBJECT_H
#include "IGameObserver.h"
#include "Enums/EGameEvent.h"

class IGameSubject {
public:
    virtual void addObserver(IGameObserver* observer);
    virtual void removeObserver(IGameObserver* observer);
    virtual void notify(EGameEvent event);
};
#endif //ISPROJECT_IGAMESUBJECT_H