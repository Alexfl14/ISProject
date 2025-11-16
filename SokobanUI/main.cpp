#include <iostream>
#include "include/GUI_View.h"
#include <Game.h>

/**
 * Sokoban Game - Observer Pattern Demo
 * 
 * Design Patterns Used:
 * - Observer Pattern: GUI_View observes Game for state changes
 * - Subject (Game) notifies Observer (GUI_View) on events
 */

int main()
{
    try {
        std::cout << "=== Sokoban Game - Observer Pattern Demo ===\n";
        std::cout << "Backend developed by your colleague\n";
        std::cout << "Frontend (Observer) implementation\n\n";
        
        // Create the Subject (Game Logic)
        Game game;
        std::cout << "Game (Subject) created\n";
        
        // Load first level
        game.loadLevel(2);
        std::cout << "Level 1 loaded\n";
        
        // Create the Observer (GUI View)
        GUI_View view(&game);
        std::cout << "GUI_View (Observer) created\n";
        
        // Register the Observer with the Subject
        game.addObserver(&view);
        std::cout << "Observer registered with Subject\n\n";
        
        // Initialize the window
        view.initialize(800, 600);
        
        std::cout << "Controls:\n";
        std::cout << "  Arrow Keys / WASD - Move player\n";
        std::cout << "  R - Restart level\n";
        std::cout << "  ESC - Exit game\n\n";
        
        // Main game loop
        while (!view.shouldClose()) {
            // Handle input (calls Game methods which notify observers)
            view.handleInput();
            
            // Render current state
            view.render();
        }
        
        // Cleanup: Unregister observer
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