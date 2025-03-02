#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height)
    : background(width, height, { "frame1.png", "frame2.png", "frame3.png", "frame4.png", "frame5.png", "frame6.png" }) {

    if (!font.loadFromFile("QABAXEL.ttf")) {
        std::cerr << "Error loading font\n";
    }

    std::string options[MENU_ITEMS] = { "Play", "Options", "Exit" };

    for (int i = 0; i < MENU_ITEMS; i++) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(40);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setPosition(width / 2 - 50, height / 2 + i * 60);
    }

    selectedItemIndex = 0;
    menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void Menu::draw(sf::RenderWindow& window) {
    background.update();
    background.draw(window);

    for (int i = 0; i < MENU_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex > 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex < MENU_ITEMS - 1) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

int Menu::getSelectedItem() {
    return selectedItemIndex;
}

void Menu::handleMouseHover(sf::Vector2f mousePos) {
    for (int i = 0; i < MENU_ITEMS; i++) {
        if (menu[i].getGlobalBounds().contains(mousePos)) {
            menu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex = i;
            menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
            break;
        }
    }
}

int Menu::handleMouseClick(sf::Vector2f mousePos) {
    for (int i = 0; i < MENU_ITEMS; i++) {
        if (menu[i].getGlobalBounds().contains(mousePos)) {
            return i;
        }
    }
    return -1;
}
