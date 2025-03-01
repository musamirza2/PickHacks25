#include "character.h"
#include "engine.h"

using namespace sf;
character::character()
{
    c_speed = 9000;
    ballShape.setRadius(8.5f);
    ballShape.setFillColor(Color::White);
    ballShape.setPosition(sf::Vector2(10000.0f, 0));

}

CircleShape character::get_ballShape()
{
    return ballShape;
}

void character::moveLeft() {
    c_leftButton = true;
}

void character::moveRight() {
    c_rightButton = true;
}
void character::moveUp() {
    c_upButton = true;
}

void character::moveDown() {
    c_downButton = true;
}

void character::stopLeft() {
    c_leftButton = false;
}

void character::stopRight() {
    c_rightButton = false;
}

void character::stopUp() {
    c_upButton = false;
}

void character::stopDown() {
    c_downButton = false;
}

void character::update(float elapsedTime) {
    Vector2f direction{ 0.f, 0.f };


    if (c_rightButton) direction.x += 1.f;
    if (c_leftButton) direction.x -= 1.f;
    if (c_upButton) direction.y -= 1.f;
    if (c_downButton) direction.y += 1.f;

    if (direction.x != 0.f || direction.y != 0.f) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); //Finds the magnitude
        direction /= length; // Normalization
        velocity += direction * acceleration * elapsedTime; //(pixles/s^2  * s)
    }
    else {
        // Apply friction if  no input (deceleration)
        if (velocity.x > 0.f || m_Position.x >= resolution) velocity.x = std::max(0.f, velocity.x - friction * elapsedTime);
        if (velocity.x < 0.f || m_Position.x >= resolution) velocity.x = std::min(0.f, velocity.x + friction * elapsedTime);
        if (velocity.y > 0.f || m_Position.y >= resolution) velocity.y = std::max(0.f, velocity.y - friction * elapsedTime);
        if (velocity.y < 0.f || m_Position.y >= resolution) velocity.y = std::min(0.f, velocity.y + friction * elapsedTime);
    }

    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y); // remove direction
    if (speed > maxSpeed) {
        velocity = (velocity / speed) * maxSpeed;
    }

    m_Position += velocity * elapsedTime;
    /*
    if (m_Position.x >= resolution) {
        // character is near right of screen
        triDirectionX = LEFT;
    }
    else if (triX < 0) {
        // character is near left of screen
        triDirectionX = RIGHT;
    }

    if (m_Position.y >= resolution) {
        // character is near bottom of screen
        triDirectionY = UP;
    }
    else if (triY < 0) {
        // character is near top of screen
        triDirectionY = DOWN;
    }
    */
    ballShape.setPosition(m_Position);

}