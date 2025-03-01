#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class orbit {
private:
    CircleShape ring;

public:
    orbit(float radius, float thickness);
    void draw(RenderWindow& window);
};
