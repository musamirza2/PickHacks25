#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "character.h"
#include "orbit.h"
#include "meteor.h"

using namespace sf;

class meteor;

class engine {
private:
    RenderWindow c_Window;
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
