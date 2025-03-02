#include "character.h"
#include "engine.h"
#include "math.h"
#include "TextureManager.h"
using namespace sf;

character::character(Vector2f spawnPosition, TextureManager& texManager)
{
    Character_sprite.setTexture(texManager.getTexture("C:/Users/solan/source/repos/PickHacks25/test/PLAYER.PNG"));

    ballShape.setRadius(15.5f);
    Character_sprite.setScale(3.f,3.f);
    ballShape.setFillColor(Color::Transparent);
    m_Position = spawnPosition;  // Set the spawn position
    ballShape.setPosition(m_Position);
    Character_sprite.setPosition(m_Position);
}

CircleShape character::get_ballShape()
{
    return ballShape;
}

const Sprite& character::getSprite() const {
    return Character_sprite;
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

    Vector2f center((VideoMode::getDesktopMode().width - 25) / 2, (VideoMode::getDesktopMode().height - 50) / 2);
    float direction = 0.f;

    float deltaX = m_Position.x - center.x;
    float deltaY = m_Position.y - center.y;
    float magnatude = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    float phasor = std::atan2(deltaY, deltaX);
    static float angularSpeed = 0.f;




    if (c_rightButton) angularSpeed -= acceleration * elapsedTime;
    if (c_leftButton) angularSpeed += acceleration * elapsedTime;

    else {
        if (angularSpeed > 0.f) angularSpeed = std::max(0.f, angularSpeed - friction * elapsedTime);
        if (angularSpeed < 0.f) angularSpeed = std::min(0.f, angularSpeed + friction * elapsedTime);
    }

    if (angularSpeed > maxSpeed) angularSpeed = maxSpeed;
    if (angularSpeed < -maxSpeed) angularSpeed = -maxSpeed;

    phasor += angularSpeed * elapsedTime;


    m_Position.x = center.x + magnatude * std::cos(phasor);
    m_Position.y = center.y + magnatude * std::sin(phasor);

    ballShape.setPosition(m_Position);
    Character_sprite.setPosition(m_Position);
}