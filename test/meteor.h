#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

using namespace sf;

class meteor {
private:
    CircleShape shape;
    Vector2f position;
    Vector2f velocity;
    Texture Rock_texture;
    Sprite Rock_sprite;
    float speed = 200.f;
    bool enteredRing = false;
    bool scored = false;

public:
    meteor(Vector2f startPosition, float size, TextureManager& texManager);
    void update(float dt);
    CircleShape getShape() const;
    bool hasEnteredRing() const;
    void markEnteredRing();
    bool hasScored() const;  // Check if the meteor has been counted
    void markScored();       // Mark the meteor as counted
    const Sprite& getSprite() const;


};
