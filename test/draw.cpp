#include "engine.h"

using namespace sf;

void engine::draw() {
    c_Window.clear();
    background.update();
    background.draw(c_Window);

    inst_orbit.draw(c_Window);
    c_Window.draw(inst_character.get_ballShape());
    c_Window.draw(inst_character.getSprite());

    for (const auto& m : meteors) {
        c_Window.draw(m.getShape());
        c_Window.draw(m.getSprite());
    }
    c_Window.draw(scoreText); // Draw the score on screen
    c_Window.draw(highScoreText); // Draw highest session score below

    c_Window.display();
}
