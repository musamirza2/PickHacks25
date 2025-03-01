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
                if (event.key.code == Keyboard::W) {
                    menu.moveUp();
                }
                else if (event.key.code == Keyboard::S) {
                    menu.moveDown();
                }
                else if (event.key.code == Keyboard::Enter) {
                    int selectedItem = menu.getSelectedItem();
                    if (selectedItem == 0) { // Play
                        isMenuActive = false;
                    }
                    else if (selectedItem == 2) { // Exit
                        c_Window.close();
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

