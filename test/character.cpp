#include "character.h"
#include "engine.h"
#include "math.h"
#include "cmath"
#include "TextureManager.h"
using namespace sf;

float pie = 3.141592653589793238462643383;

character::character(Vector2f spawnPosition, TextureManager& texManager)
{
    Character_sprite.setTexture(texManager.getTexture("PLAYER.PNG"));
    FloatRect spriteBounds = Character_sprite.getGlobalBounds();
    float spriteDiameter = std::max(spriteBounds.width, spriteBounds.height);
    m_Position = spawnPosition;  // Set the spawn position

    // Adjust ballShape to match sprite size
    ballShape.setRadius(spriteDiameter);
    ballShape.setFillColor(Color::Transparent);

    ballShape.setOrigin(ballShape.getRadius(), ballShape.getRadius());
    Character_sprite.setOrigin(Character_sprite.getTexture()->getSize().x / 2.f, Character_sprite.getTexture()->getSize().y / 2.f);

    Character_sprite.setScale(3.f, 3.f);


    ballShape.setPosition(m_Position);
    Character_sprite.setPosition(m_Position);

}

const CircleShape& character::get_ballShape() const {
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
    // Angular acceleration control
    if (c_rightButton) angularVelocity -= acceleration * elapsedTime;  // Clockwise
    if (c_leftButton) angularVelocity += acceleration * elapsedTime;   // Counterclockwise
    else {
        // Apply friction when no input
        if (angularVelocity > 0.f) angularVelocity = std::max(0.f, angularVelocity - friction * elapsedTime);
        if (angularVelocity < 0.f) angularVelocity = std::min(0.f, angularVelocity + friction * elapsedTime);
    }

    // Clamp angular velocity
    if (angularVelocity > maxSpeed) angularVelocity = maxSpeed;
    if (angularVelocity < -maxSpeed) angularVelocity = -maxSpeed;

    // Update angle based on velocity
    angle += angularVelocity * elapsedTime;

    // Convert polar coordinates to Cartesian position
    m_Position.x = center.x + radius * std::cos(angle);
    m_Position.y = center.y + radius * std::sin(angle);

    // Ensure tangential direction
    float tangentX = -std::sin(angle);  // Derivative of cos(angle)
    float tangentY = std::cos(angle);   // Derivative of sin(angle)

    // Update character position
    ballShape.setPosition(m_Position);
    Character_sprite.setPosition(m_Position);

    if (angularVelocity > 0) {
        Character_sprite.setScale(3.f, -3.f);  // Face right
    }
    else if (angularVelocity < 0) {
        Character_sprite.setScale(3.f, 3.f); // Face left
    }

 
    float rotationAngle = std::atan2(tangentY, tangentX) * 180.f / pie; // pie
    Character_sprite.setRotation(rotationAngle-90);
}