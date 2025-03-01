#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

const int MENU_ITEMS = 3;

class Menu {
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MENU_ITEMS];

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItem();
};

#endif

