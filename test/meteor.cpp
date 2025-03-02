#include "meteor.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "TextureManager.h"

meteor::meteor(Vector2f startPosition, float size, TextureManager& texManager) {
    Rock_sprite.setTexture(texManager.getTexture("C:/Users/solan/source/repos/PickHacks25/test/ROCK1.PNG"));
    position = startPosition;

    // Set meteor size
    shape.setRadius(size);
    shape.setFillColor(Color::Black);
    shape.setPosition(position);

    // Randomize velocity towards the center of the screen
    Vector2f center(960.f, 540.f); // Assuming screen center for 1920x1080
    Vector2f direction = center - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = direction / length * speed;
    float radius = shape.getRadius();

    Vector2u textureSize = Rock_sprite.getTexture()->getSize();

    float scaleFactor = (radius * 2) / static_cast<float>(textureSize.x);
    Rock_sprite.setScale(scaleFactor, scaleFactor);

    Rock_sprite.setPosition(position);
}
bool meteor::hasEnteredRing() const {
    return enteredRing;
}
void meteor::markEnteredRing() {
    enteredRing = true;
}
bool meteor::hasScored() const {
    return scored;
}
void meteor::markScored() {
    scored = true;
}

void meteor::update(float dt) {
    position += velocity * dt;
    shape.setPosition(position);
    Rock_sprite.setPosition(position);
}

CircleShape meteor::getShape() const {
    return shape;
}

const Sprite& meteor::getSprite() const {
    return Rock_sprite;
}

void meteor::setSpeed(float newSpeed) {
    speed = newSpeed;
    if (std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > 0) {
        velocity = (velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y)) * speed;
    }
}
