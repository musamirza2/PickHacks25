#include "meteor.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "TextureManager.h"

meteor::meteor(Vector2f startPosition, float size, TextureManager& texManager) {
    Rock_sprite.setTexture(texManager.getTexture("C:/Users/solan/source/repos/PickHacks25/test/ROCK.PNG"));
    position = startPosition;

    // Set meteor size
    shape.setRadius(size);
    shape.setFillColor(Color::Yellow);
    shape.setPosition(position);

    // Randomize velocity towards the center of the screen
    Vector2f center(960.f, 540.f); // Assuming screen center for 1920x1080
    Vector2f direction = center - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = direction / length * speed;
    Rock_sprite.setScale(Vector2(shape.getScale().x * 3, shape.getScale().y * 3));

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
