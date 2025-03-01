#include "engine.h"

using namespace sf;

void engine::update(float dtAsSeconds) {
    inst_character.update(dtAsSeconds);

    if (meteorSpawnClock.getElapsedTime().asSeconds() > 1.5f) {
        spawnMeteor();
        meteorSpawnClock.restart();
    }

    for (auto& m : meteors) {
        m.update(dtAsSeconds);
    }

    if (checkCollision()) {
        gamePaused = true;
    }
}