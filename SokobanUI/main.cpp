#include <iostream>
#include "include/GUI_View.h"
#include <Game.h>

int main()
{
    try {
        std::cout << "=== Sokoban Game - Observer Pattern Demo ===\n";
        std::cout << "Backend developed by your colleague\n";
        std::cout << "Frontend (Observer) implementation\n\n";
        
        Game game;
        std::cout << "Game (Subject) created\n";
        
        game.loadLevel(1);
        std::cout << "Level 1 loaded\n";
        
        GUI_View view(&game);
        std::cout << "GUI_View (Observer) created\n";
        
        game.addObserver(&view);
        std::cout << "Observer registered with Subject\n\n";
        
        view.initialize(800, 600);
        
        std::cout << "Controls:\n";
        std::cout << "  Arrow Keys / WASD - Move player\n";
        std::cout << "  R - Restart level\n";
        std::cout << "  ESC - Exit game\n\n";
        
        while (!view.shouldClose()) {
            view.handleInput();
            
            view.render();
        }
        
        game.removeObserver(&view);
        std::cout << "\nObserver unregistered from Subject\n";
        
        view.cleanup();
        
        std::cout << "Game closed. Thanks for playing!\n";
        std::cout << "Observer Pattern successfully demonstrated!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}