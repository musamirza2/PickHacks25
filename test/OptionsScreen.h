#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

class OptionsScreen {
public:
    OptionsScreen(float width, float height);  // Constructor

    // Event handling for mouse interactions
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& inOptions, bool& inMenu);

    // Function to draw the options screen
    void draw(sf::RenderWindow& window);

    // Getter functions
    std::string getDifficulty() const;  // Returns "Easy" or "Hard"
    int getVolume() const;  // Returns volume slider value

private:
    sf::RectangleShape easyButton;
    sf::RectangleShape hardButton;
    sf::RectangleShape backButton;
    sf::RectangleShape volumeSlider;

    int currentVolume = 50;  // Ensure `currentVolume` is properly initialized
    int selectedOption = 0;  // Tracks which option is selected
    std::string difficulty = "Easy"; // Default difficulty setting

    sf::Text easyLabel;
    sf::Text hardLabel;
    sf::Text volumeText;
    sf::Text backButtonText;

    sf::Font font;
};

#endif
