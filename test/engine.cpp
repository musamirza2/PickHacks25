#include <SFML/Graphics.hpp>
#include "engine.h"

using namespace sf;

engine::engine() {
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	c_Window.create(VideoMode(resolution.x, resolution.y),
		"Simple Game Engine",
		Style::Fullscreen);
}
void engine::start() {
	Clock clock;
	while (c_Window.isOpen()) {
		Time dt = clock.restart();
		dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}
/*
Vector2f get_resolution() {
	return c_Window;
}
*/