#include "engine.h"

using namespace sf;

void engine::draw() {
	c_Window.clear(Color::Black);

	c_Window.draw(inst_character.get_ballShape());

	c_Window.display();
}