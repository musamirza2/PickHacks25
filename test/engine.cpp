#include "engine.h"
#include "meteor.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;

engine::engine() : menu(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height) {
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    c_Window.create(VideoMode(resolution.x, resolution.y), "Simple Game Engine", Style::Fullscreen);
    std::srand(static_cast<unsigned int>(std::time(0)));
}

void engine::start() {
    Clock clock;
    while (c_Window.isOpen()) {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input(); // Calls input() from input.cpp

        if (isMenuActive) {
            c_Window.clear();
            menu.draw(c_Window);
            c_Window.display();
        }
        else {
            if (!gamePaused) {
                update(dtAsSeconds); // Calls update() from update.cpp
            }
            draw(); // Calls draw() from draw.cpp
        }
    }
}

void engine::spawnMeteor() {
    meteors.emplace_back(c_Window.getSize());
}

bool engine::checkCollision() {
    CircleShape ball = inst_character.get_ballShape();
    Vector2f ballPos = ball.getPosition();
    float ballRadius = ball.getRadius();

    for (const auto& m : meteors) {
        CircleShape meteorShape = m.getShape();
        Vector2f meteorPos = meteorShape.getPosition();
        float meteorRadius = meteorShape.getRadius();

        float dx = ballPos.x - meteorPos.x;
        float dy = ballPos.y - meteorPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < (ballRadius + meteorRadius)) {
            return true;
        }
    }
    return false;
}
