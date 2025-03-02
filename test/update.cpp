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
        float meteorRadius = m.getShape().getRadius();
        Vector2f meteorPos = m.getShape().getPosition();
        Vector2f center(c_Window.getSize().x / 2, c_Window.getSize().y / 2);
        float distance = std::sqrt(std::pow(meteorPos.x - center.x, 2) + std::pow(meteorPos.y - center.y, 2));

        // Check if meteor has entered the ring
        if (distance < 100.0f && !m.hasEnteredRing()) {  // Assuming orbit radius is 100
            m.markEnteredRing();
        }

        // Check if meteor has exited the ring successfully without collision
        if (distance > 150.0f && m.hasEnteredRing() && !m.hasScored()) {  // Assuming exit threshold is 150
            if (!checkCollision()) {
                if (meteorRadius < 15.0f) { // Small meteor
                    increaseScore(1);
                }
                else { // Large meteor
                    increaseScore(5);
                }
                m.markScored();
            }
        }
    }


    if (checkCollision()) {
        gamePaused = true;
    }

}
