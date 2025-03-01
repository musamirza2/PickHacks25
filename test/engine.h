#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"
#include "orbit.h"

using namespace sf;

class engine {
private:
    RenderWindow c_Window;
    orbit inst_orbit = orbit(100.f, 5.f); // White ring with radius 100, thickness 5

    // Character spawns on the orbit’s edge (center + radius, assuming 1920x1080 resolution)
    character inst_character = character(Vector2f(960.f + 85.0f, 540.f));

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    engine();
    float dtAsSeconds;
    void start();
};
