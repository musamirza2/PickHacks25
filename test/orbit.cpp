#include "orbit.h"

orbit::orbit(float radius, float thickness) {
    ring.setRadius(radius);
    ring.setPointCount(100); // Smooth circle
    ring.setOutlineThickness(thickness);
    ring.setOutlineColor(Color::White);
    ring.setFillColor(Color::Transparent);
}

void orbit::draw(RenderWindow& window) {
    // Center the ring in the window
    Vector2u windowSize = window.getSize();
    ring.setPosition(
        (windowSize.x / 2) - ring.getRadius(),
        (windowSize.y / 2) - ring.getRadius()
    );

    window.draw(ring);
}
