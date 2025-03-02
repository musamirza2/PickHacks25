#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Background.h" // Added background support

class OptionsScreen {
public:
    OptionsScreen(float width, float height);  // Constructor

    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& inOptions, bool& inMenu);
    void draw(sf::RenderWindow& window);

    std::string getDifficulty() const;
    int getVolume() const;

private:
    Background background; // Background animation

    sf::RectangleShape easyButton;
    sf::RectangleShape hardButton;
    sf::RectangleShape backButton;
    sf::RectangleShape volumeSlider;

    int currentVolume = 50;
    int selectedOption = 0;
    std::string difficulty = "Easy";

    sf::Text easyLabel;
    sf::Text hardLabel;
    sf::Text volumeText;
    sf::Text backButtonText;

    sf::Font font;
};

#endif
