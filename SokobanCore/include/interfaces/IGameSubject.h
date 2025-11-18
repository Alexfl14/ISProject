//
// Created by fafa on 12.11.2025.
//

#ifndef ISPROJECT_IGAMESUBJECT_H
#define ISPROJECT_IGAMESUBJECT_H
#include "IGameObserver.h"
#include "enums/EGameEvent.h"

class IGameSubject {
public:
    virtual ~IGameSubject() = default;
    virtual void addObserver(IGameObserver* observer) = 0;
    virtual void removeObserver(IGameObserver* observer) = 0;
    virtual void notify(EGameEvent event) = 0;
};

#endif //ISPROJECT_IGAMESUBJECT_H
