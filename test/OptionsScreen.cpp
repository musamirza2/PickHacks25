#include "OptionsScreen.h"

OptionsScreen::OptionsScreen(float width, float height) {
    if (!font.loadFromFile("QABAXEL.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // Initialize buttons
    easyButton.setSize(sf::Vector2f(200, 50));
    easyButton.setPosition(width / 2 - 100, height / 3);
    easyButton.setFillColor(sf::Color::Black);

    hardButton.setSize(sf::Vector2f(200, 50));
    hardButton.setPosition(width / 2 - 100, height / 3 + 60);
    hardButton.setFillColor(sf::Color::Black);

    backButton.setSize(sf::Vector2f(200, 50));
    backButton.setPosition(width / 2 - 100, height / 3 + 120);
    backButton.setFillColor(sf::Color::Black);

    // Initialize labels
    easyLabel.setFont(font);
    easyLabel.setString("Easy");
    easyLabel.setCharacterSize(24);
    easyLabel.setFillColor(sf::Color::White);
    easyLabel.setPosition(easyButton.getPosition().x + 70, easyButton.getPosition().y + 10);

    hardLabel.setFont(font);
    hardLabel.setString("Hard");
    hardLabel.setCharacterSize(24);
    hardLabel.setFillColor(sf::Color::White);
    hardLabel.setPosition(hardButton.getPosition().x + 70, hardButton.getPosition().y + 10);

    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(24);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(backButton.getPosition().x + 70, backButton.getPosition().y + 10);

    // Initialize volume slider
    volumeSlider.setSize(sf::Vector2f(200, 10));
    volumeSlider.setPosition(width / 2 - 100, height / 2 + 80);
    volumeSlider.setFillColor(sf::Color::Blue);

    volumeText.setFont(font);
    volumeText.setString("Volume: " + std::to_string(currentVolume)); // Uses `currentVolume`
    volumeText.setCharacterSize(24);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setPosition(volumeSlider.getPosition().x, volumeSlider.getPosition().y - 30);
}

void OptionsScreen::handleEvent(sf::Event event, sf::RenderWindow& window, bool& inOptions, bool& inMenu) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

    // Detect mouse hover over buttons
    if (easyButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = 0;  // Highlight Easy
    }
    else if (hardButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = 1;  // Highlight Hard
    }
    else if (backButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = 2;  // Highlight Back
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedOption = (selectedOption - 1 + 3) % 3;  // Wrap around selection
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedOption = (selectedOption + 1) % 3;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) {
                difficulty = "Easy";  // Set difficulty to Easy
            }
            else if (selectedOption == 1) {
                difficulty = "Hard";  //Set difficulty to Hard
            }
            else if (selectedOption == 2) {
                inOptions = false;   // Exit to Main Menu
                inMenu = true;
            }
        }
    }

    // Fix: Allow mouse scrolling for volume slider
    if (event.type == sf::Event::MouseWheelMoved) {
        currentVolume += event.mouseWheel.delta * 5;
        if (currentVolume < 0) currentVolume = 0;
        if (currentVolume > 100) currentVolume = 100;

        volumeText.setString("Volume: " + std::to_string(currentVolume));  // Update text dynamically
    }

    //Fix: Handle Mouse Click Selection
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (easyButton.getGlobalBounds().contains(mousePos)) {
                difficulty = "Easy";
            }
            else if (hardButton.getGlobalBounds().contains(mousePos)) {
                difficulty = "Hard";
            }
            else if (backButton.getGlobalBounds().contains(mousePos)) {
                inOptions = false;
                inMenu = true;
            }
        }
    }
}


void OptionsScreen::draw(sf::RenderWindow& window) {
    // Default button and text colors
    easyButton.setFillColor(sf::Color::Black);
    easyLabel.setFillColor(sf::Color::White);

    hardButton.setFillColor(sf::Color::Black);
    hardLabel.setFillColor(sf::Color::White);

    backButton.setFillColor(sf::Color::Black);
    backButtonText.setFillColor(sf::Color::White);

    // Highlight the selected option (Yellow Button with Black Text)
    if (selectedOption == 0) {
        easyButton.setFillColor(sf::Color::Yellow);
        easyLabel.setFillColor(sf::Color::Black);
    }
    else if (selectedOption == 1) {
        hardButton.setFillColor(sf::Color::Yellow);
        hardLabel.setFillColor(sf::Color::Black);
    }
    else if (selectedOption == 2) {
        backButton.setFillColor(sf::Color::Yellow);
        backButtonText.setFillColor(sf::Color::Black);
    }

    // Draw all elements
    window.draw(easyButton);
    window.draw(hardButton);
    window.draw(backButton);
    window.draw(volumeSlider);

    window.draw(easyLabel);
    window.draw(hardLabel);
    window.draw(backButtonText);
    window.draw(volumeText);
}
