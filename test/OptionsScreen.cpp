#include "OptionsScreen.h"

OptionsScreen::OptionsScreen(float width, float height)
    : background(width, height, { "frame1.png", "frame2.png", "frame3.png", "frame4.png", "frame5.png", "frame6.png" }) { // Load animated background

    if (!font.loadFromFile("QABAXEL.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // Initialize buttons (Transparent background)
    easyButton.setSize(sf::Vector2f(200, 50));
    easyButton.setPosition(width / 2 - 100, height / 3);
    easyButton.setFillColor(sf::Color::Transparent);


    hardButton.setSize(sf::Vector2f(200, 50));
    hardButton.setPosition(width / 2 - 100, height / 3 + 120);
    hardButton.setFillColor(sf::Color::Transparent);

    backButton.setSize(sf::Vector2f(200, 50));
    backButton.setPosition(width / 2 - 100, height / 3 + 200);
    backButton.setFillColor(sf::Color::Transparent);

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
    volumeSlider.setPosition(width / 2 - 100, height / 2 + 100);
    volumeSlider.setFillColor(sf::Color::Blue);

    volumeText.setFont(font);
    volumeText.setString("Volume: " + std::to_string(currentVolume));
    volumeText.setCharacterSize(24);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setPosition(volumeSlider.getPosition().x, volumeSlider.getPosition().y - 30);
}

void OptionsScreen::handleEvent(sf::Event event, sf::RenderWindow& window, bool& inOptions, bool& inMenu) {
    sf::Vector2f mousePos(sf::Mouse::getPosition(window));

    // Detect mouse hover over buttons
    if (easyButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = 0;
    }
    else if (hardButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = 1;
    }
    else if (backButton.getGlobalBounds().contains(mousePos)) {
        selectedOption = 2;
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedOption = (selectedOption - 1 + 3) % 3;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedOption = (selectedOption + 1) % 3;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) {
                difficulty = "Easy";
            }
            else if (selectedOption == 1) {
                difficulty = "Hard";
            }
            else if (selectedOption == 2) {
                inOptions = false;
                inMenu = true;
            }
        }
    }

    // Allow mouse scrolling for volume slider
    if (event.type == sf::Event::MouseWheelMoved) {
        currentVolume += event.mouseWheel.delta * 5;
        if (currentVolume < 0) currentVolume = 0;
        if (currentVolume > 100) currentVolume = 100;

        volumeText.setString("Volume: " + std::to_string(currentVolume));
    }

    // Handle Mouse Click Selection
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
    background.update();
    background.draw(window);

    // Keep buttons transparent
    easyButton.setFillColor(sf::Color::Transparent);
    hardButton.setFillColor(sf::Color::Transparent);
    backButton.setFillColor(sf::Color::Transparent);

    // Default text color
    easyLabel.setFillColor(sf::Color::White);
    hardLabel.setFillColor(sf::Color::White);
    backButtonText.setFillColor(sf::Color::White);

    // Highlight the selected text only
    if (selectedOption == 0) {
        easyLabel.setFillColor(sf::Color::Yellow);
    }
    else if (selectedOption == 1) {
        hardLabel.setFillColor(sf::Color::Yellow);
    }
    else if (selectedOption == 2) {
        backButtonText.setFillColor(sf::Color::Yellow);
    }

    // Draw everything
    window.draw(easyButton);
    window.draw(hardButton);
    window.draw(backButton);
    window.draw(volumeSlider);

    window.draw(easyLabel);
    window.draw(hardLabel);
    window.draw(backButtonText);
    window.draw(volumeText);
}
