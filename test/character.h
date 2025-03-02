#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

using namespace sf;

class character {
private:
    float angle = 0.f;  // Angle in radians
    Vector2f center = { 960.f, 540.f };  // Center of movement
    float radius = 200.f;  // Fixed orbit radius
    float angularVelocity = 0.f;  // Speed along orbit

    Vector2f m_Position;
    float acceleration = 10.f;
    float friction = 8.0f;
    float maxSpeed = 10.f;
    CircleShape ballShape;
    Texture Character_texture;
    Sprite Character_sprite;


    // Where character is currently moving
    bool c_leftButton{};
    bool c_rightButton{};
    bool c_downButton{};
    bool c_upButton{};

public:
    character(Vector2f spawnPosition, TextureManager& texManager); // Updated constructor
    const CircleShape &get_ballShape() const;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    const Sprite& getSprite() const;

    void update(float elapsedTime);
};