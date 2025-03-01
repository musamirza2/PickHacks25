#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class character {
private:
    Vector2f m_Position;
    Vector2f velocity = { 0.f, 0.f };
    float acceleration = 3000.f;
    float friction = 2000.f;
    float maxSpeed = 9000.f;
    CircleShape ballShape;

    // Where character is currently moving
    bool c_leftButton{};
    bool c_rightButton{};
    bool c_downButton{};
    bool c_upButton{};

public:
    character(Vector2f spawnPosition); // Updated constructor
    CircleShape get_ballShape();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    void update(float elapsedTime);
};
