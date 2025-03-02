#include "engine.h"
#include "meteor.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

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
    isMenuActive = true; // Ensure the game starts at the menu

    while (c_Window.isOpen()) {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();

        if (isGameOver) {
            handleGameOver(); // Handles game over transition
        }
        else if (isMenuActive) {
            c_Window.clear();
            menu.draw(c_Window);
            c_Window.display();
        }
        else {
            if (!gamePaused) {
                update(dtAsSeconds);
            }
            draw();
        }
    }
}

void engine::handleGameOver() {
    c_Window.clear();
    Font font;
    if (!font.loadFromFile("QABAXEL.ttf")) {
        std::cerr << "Error loading font\n";
    }

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(800, 300);

    c_Window.draw(gameOverText);
    c_Window.display();

    if (gameOverClock.getElapsedTime().asSeconds() > 1.0f) {  //  Show for 1 second
        isGameOver = false;
        isMenuActive = true; //  Automatically go back to the main menu
    }
}

void engine::resetGame() {
    meteors.clear();
    inst_character = character(Vector2f(960.f + 85.0f, 540.f));
    gamePaused = false;
    isGameOver = false;
    isMenuActive = false;
    meteorSpawnClock.restart();
}

void engine::spawnMeteor() {  // Define spawnMeteor() here
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
            isGameOver = true;
            gameOverClock.restart();  //  Start game over timer
            return true;
        }
    }
    return false;
}
