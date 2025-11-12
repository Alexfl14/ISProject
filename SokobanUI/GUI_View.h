//
// Created by fafa on 12.11.2025.
//

#ifndef SOKOBANGAME_GUI_VIEW_H
#define SOKOBANGAME_GUI_VIEW_H

#include <Interfaces/IGame.h>
#include <Enums/EGameEvent.h>

class GUI_View{
public:
    GUI_View();
    void onNotify(EGameEvent event);
    void render();
    void handleInputKey(KeyCode key);
private:
    IGame* gameLogic;
};


#endif //SOKOBANGAME_GUI_VIEW_H