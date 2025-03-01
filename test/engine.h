#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"

using namespace sf;

class engine {
private:
    RenderWindow c_Window;

    character inst_character;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    RenderWindow get_resolution;
    engine();
    float dtAsSeconds;
    void start();

};