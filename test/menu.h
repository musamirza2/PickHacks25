#pragma once
#include <SFML/Graphics.hpp>

#define MENU_ITEMS 3

class Menu {
private:
    sf::Font font;
    sf::Text menu[MENU_ITEMS];
    int selectedItemIndex;

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItem();

    // New functions for Mouse Hover & Click
    void handleMouseHover(sf::Vector2f mousePos);
    int handleMouseClick(sf::Vector2f mousePos);
};
