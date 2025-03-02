#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
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

// Handle Mouse Hover Effect
void Menu::handleMouseHover(sf::Vector2f mousePos) {
    for (int i = 0; i < MENU_ITEMS; i++) {
        if (menu[i].getGlobalBounds().contains(mousePos)) {
            menu[selectedItemIndex].setFillColor(sf::Color::White); // Reset old selection
            selectedItemIndex = i; // Update selection
            menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
            break;
        }
    }
}

// Handle Mouse Click Selection
int Menu::handleMouseClick(sf::Vector2f mousePos) {
    for (int i = 0; i < MENU_ITEMS; i++) {
        if (menu[i].getGlobalBounds().contains(mousePos)) {
            return i; // Return index of clicked menu item
        }
    }
    return -1; // No selection
}
