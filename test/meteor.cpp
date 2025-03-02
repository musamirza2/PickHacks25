#include "meteor.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

meteor::meteor(Vector2f startPosition, float size) {
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
}

CircleShape meteor::getShape() const {
    return shape;
}
