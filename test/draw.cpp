#include "engine.h"

using namespace sf;

void engine::draw() {
    c_Window.clear(Color::Black);

    inst_orbit.draw(c_Window);  // Draw the orbit (ring)
    c_Window.draw(inst_character.get_ballShape());  // Draw the character

    c_Window.display();
}
