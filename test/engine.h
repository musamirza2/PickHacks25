#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "meteor.h"
#include "Menu.h"
#include "character.h"
#include "orbit.h"

using namespace sf;

class engine {
private:
    RenderWindow c_Window;
    Menu menu;
    bool isMenuActive = true;
    orbit inst_orbit = orbit(100.f, 5.f);
    character inst_character = character(Vector2f(960.f + 85.0f, 540.f));

    std::vector<meteor> meteors;
    Clock meteorSpawnClock;
    bool gamePaused = false;

    void spawnMeteor();
    void input();
    void update(float dtAsSeconds);
    void draw();
    bool checkCollision();

public:
    engine();
    void start();
};
