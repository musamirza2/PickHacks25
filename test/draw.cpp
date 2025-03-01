#include "engine.h"

using namespace sf;

void engine::draw() {
    c_Window.clear(Color::Black);

    inst_orbit.draw(c_Window);
    c_Window.draw(inst_character.get_ballShape());

    for (const auto& m : meteors) {
        c_Window.draw(m.getShape());
    }

    c_Window.display();
}
