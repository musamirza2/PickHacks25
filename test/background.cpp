#include "Background.h"
#include <iostream>

Background::Background(float width, float height, std::vector<std::string> frameFiles)
    : currentFrame(0), frameTime(0.15f) {  // Frame switch time
    for (const auto& file : frameFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(file)) {
            std::cerr << "Error loading background frame: " << file << std::endl;
        }
        else {
            frames.push_back(texture);
        }
    }

    if (!frames.empty()) {
        backgroundSprite.setTexture(frames[0]);
        backgroundSprite.setScale(width / frames[0].getSize().x, height / frames[0].getSize().y);
    }
}

void Background::update() {
    if (animationClock.getElapsedTime().asSeconds() > frameTime) {
        currentFrame = (currentFrame + 1) % frames.size();
        backgroundSprite.setTexture(frames[currentFrame]);
        animationClock.restart();
    }
}

void Background::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
}
