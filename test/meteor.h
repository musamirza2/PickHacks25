#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class meteor {
private:
    CircleShape shape;
    Vector2f position;
    Vector2f velocity;
    float speed = 200.f;

public:
    meteor(Vector2u windowSize);
    void update(float dt);
    CircleShape getShape() const;
};
