#include "meteor.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "TextureManager.h"

meteor::meteor(Vector2f startPosition, float size, TextureManager& texManager) {
    Rock_sprite.setTexture(texManager.getTexture("ROCK1.PNG"));
    position = startPosition;

    // Set meteor hitbox size
    shape.setRadius(size);
    shape.setFillColor(Color::Black);

    // Center hitbox and sprite
    shape.setOrigin(size, size);
    Rock_sprite.setOrigin(Rock_sprite.getTexture()->getSize().x / 2.f, Rock_sprite.getTexture()->getSize().y / 2.f);

    // Scale sprite to match hitbox
    float scaleFactor = (size * 2) / static_cast<float>(Rock_sprite.getTexture()->getSize().x);
    Rock_sprite.setScale(scaleFactor - 0.25f, scaleFactor - 0.25f);

    // Set position
    shape.setPosition(position);
    Rock_sprite.setPosition(position);

    // Set velocity towards the center
    Vector2f center(960.f, 540.f); // Assuming screen center for 1920x1080
    Vector2f direction = center - position;
    velocity = (direction / std::sqrt(direction.x * direction.x + direction.y * direction.y)) * speed;
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
