#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class meteor {
private:
    CircleShape shape;
    Vector2f position;
    Vector2f velocity;
    float speed = 200.f;
    bool enteredRing = false;
    bool scored = false;

public:
    meteor(Vector2f startPosition, float size);
    meteor(Vector2u windowSize);
    void update(float dt);
    CircleShape getShape() const;
    bool hasEnteredRing() const;
    void markEnteredRing();
    bool hasScored() const;  // Check if the meteor has been counted
    void markScored();       // Mark the meteor as counted

};
