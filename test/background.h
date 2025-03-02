#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Background {
private:
    std::vector<sf::Texture> frames;
    sf::Sprite backgroundSprite;
    int currentFrame;
    float frameTime;
    sf::Clock animationClock;

public:
    Background(float width, float height, std::vector<std::string> frameFiles);

    void update();
    void draw(sf::RenderWindow& window);
};

