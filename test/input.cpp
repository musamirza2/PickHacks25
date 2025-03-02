#include "engine.h"

using namespace sf;

void engine::input() {
    Event event;
    while (c_Window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            c_Window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            c_Window.close();
        }

        if (isMenuActive) {
            if (event.type == Event::MouseMoved) {
                menu.handleMouseHover(Vector2f(event.mouseMove.x, event.mouseMove.y)); //Mouse Hover
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int clickedOption = menu.handleMouseClick(Vector2f(event.mouseButton.x, event.mouseButton.y)); // Mouse Click

                    if (clickedOption == 0) {  // Play
                        resetGame();
                    }
                    else if (clickedOption == 1) {  // Options
                        isMenuActive = false;
                        isOptionsActive = true;
                    }
                    else if (clickedOption == 2) {  // Exit
                        c_Window.close();
                    }
                }
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
                    menu.moveUp();
                }
                else if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
                    menu.moveDown();
                }
                else if (event.key.code == Keyboard::Enter) {
                    int selectedItem = menu.getSelectedItem();
                    if (selectedItem == 0) {  // Play
                        resetGame();
                    }
                    else if (selectedItem == 1) {  // Options
                        isMenuActive = false;
                        isOptionsActive = true;
                    }
                    else if (selectedItem == 2) {  // Exit
                        c_Window.close();
                    }
                }
            }
        }
        else if (isGameOver) {
            if (gameOverClock.getElapsedTime().asSeconds() > 1.0f) {
                isGameOver = false;
                isMenuActive = true;
                return;
            }

            if (event.type == Event::MouseMoved) {
                if (gameOverSelection == 0 && event.mouseMove.y > 450) {
                    gameOverSelection = 1;  // Move down when mouse hovers "Main Menu"
                }
                else if (gameOverSelection == 1 && event.mouseMove.y < 450) {
                    gameOverSelection = 0;  // Move up when mouse hovers "Replay"
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gameOverSelection == 0) {  // Replay
                        resetGame();
                    }
                    else if (gameOverSelection == 1) {  // Main Menu
                        isGameOver = false;
                        isMenuActive = true;
                    }
                }
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
                    gameOverSelection = 0;
                }
                else if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
                    gameOverSelection = 1;
                }
                else if (event.key.code == Keyboard::Enter) {
                    if (gameOverSelection == 0) {  // Replay
                        resetGame();
                    }
                    else if (gameOverSelection == 1) {  // Main Menu
                        isGameOver = false;
                        isMenuActive = true;
                    }
                }
            }
        }
        else {
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
