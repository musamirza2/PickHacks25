#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"
#include "orbit.h" // Include the orbit class

using namespace sf;

class engine {
private:
    RenderWindow c_Window;

    character inst_character;
    orbit inst_orbit = orbit(100.f, 5.f); // Creates a white ring with radius 100 and thickness 5

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    engine();
    float dtAsSeconds;
    void start();
};
