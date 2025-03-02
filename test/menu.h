#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Background.h"

#define MENU_ITEMS 3

class Menu {
private:
    sf::Font font;
    sf::Text menu[MENU_ITEMS];
    sf::Text titleText;
    int selectedItemIndex;
    sf::Music backgroundMusic;

    // Background
    Background background;

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItem();

    // Mouse interaction functions
    void handleMouseHover(sf::Vector2f mousePos);
    int handleMouseClick(sf::Vector2f mousePos);
};
