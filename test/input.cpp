#include "engine.h"

using namespace sf;

void engine::input() {
    Event event;
    while (c_Window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            c_Window.close();
        }

        // Escape will close the window
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            c_Window.close();
        }

        if (isMenuActive) {
            // Menu Navigation
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
                    menu.moveUp();
                }
                else if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
                    menu.moveDown();
                }
                else if (event.key.code == Keyboard::Enter) {
                    int selectedItem = menu.getSelectedItem();
                    if (selectedItem == 0) { // Play
                        resetGame(); //  Properly resets game
                    }
                    else if (selectedItem == 2) { // Exit
                        c_Window.close();
                    }
                }
            }
        }
        else if (isGameOver) {
            // Game Over handling
            if (gameOverClock.getElapsedTime().asSeconds() > 1.0f) { //  Wait 1 second before returning to menu
                isGameOver = false;
                isMenuActive = true;
                return; //  Ensure no other input is processed after switching
            }

            // Game Over Menu Navigation
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W) {
                    gameOverSelection = 0;
                }
                else if (event.key.code == Keyboard::S) {
                    gameOverSelection = 1;
                }
                else if (event.key.code == Keyboard::Enter) {
                    if (gameOverSelection == 0) { // Replay
                        resetGame(); // Reset and continue
                    }
                    else if (gameOverSelection == 1) { // Main Menu
                        isGameOver = false;
                        isMenuActive = true;
                    }
                }
            }
        }
        else {
            // Handle the player moving
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                inst_character.moveLeft();
            }
            else {
                inst_character.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D)) {
                inst_character.moveRight();
            }
            else {
                inst_character.stopRight();
            }
        }
    }
}
