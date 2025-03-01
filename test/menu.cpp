#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("QABAXEL.ttf")) { // Use a valid font in the project folder
        std::cerr << "Error loading font\n";
    }

    std::string options[MENU_ITEMS] = { "Play", "Options", "Exit" };

    for (int i = 0; i < MENU_ITEMS; i++) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(40);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setPosition(width / 2 - 50, height / 2 + i * 50);
    }

    selectedItemIndex = 0;
    menu[selectedItemIndex].setFillColor(sf::Color::Green);
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MENU_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex > 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex < MENU_ITEMS - 1) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}

int Menu::getSelectedItem() {
    return selectedItemIndex;
}