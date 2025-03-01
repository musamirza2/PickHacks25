#include "meteor.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

meteor::meteor(Vector2u windowSize) {
    std::srand(static_cast<unsigned int>(std::time(0)));

    float radius = 10.f + static_cast<float>(std::rand() % 21);
    shape.setRadius(radius);
    shape.setFillColor(Color::Yellow);

    int side = std::rand() % 4;
    float x, y;

    if (side == 0) {
        x = std::rand() % windowSize.x;
        y = -radius * 2;
    }
    else if (side == 1) {
        x = std::rand() % windowSize.x;
        y = windowSize.y + radius * 2;
    }
    else if (side == 2) {
        x = -radius * 2;
        y = std::rand() % windowSize.y;
    }
    else {
        x = windowSize.x + radius * 2;
        y = std::rand() % windowSize.y;
    }

    position = { x, y };
    shape.setPosition(position);

    Vector2f center(windowSize.x / 2, windowSize.y / 2);
    Vector2f direction = center - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = direction / length * speed;
}

void meteor::update(float dt) {
    position += velocity * dt;
    shape.setPosition(position);
}

CircleShape meteor::getShape() const {
    return shape;
}
