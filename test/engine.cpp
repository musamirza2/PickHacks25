#include "engine.h"
#include "meteor.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace sf;

engine::engine()
    : menu(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height),
        background(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height,
            { "frame1.png", "frame2.png", "frame3.png", "frame4.png", "frame5.png", "frame6.png" }) {
    Vector2f resolution;
    resolution.x = static_cast<float>(VideoMode::getDesktopMode().width);
    resolution.y = static_cast<float>(VideoMode::getDesktopMode().height);

    c_Window.create(VideoMode(static_cast<unsigned int>(resolution.x), static_cast<unsigned int>(resolution.y)),
        "Simple Game Engine", Style::Fullscreen);

    std::srand(static_cast<unsigned int>(std::time(0)));

    if (!font.loadFromFile("QABAXEL.ttf")) { // Ensure this font file exists
        std::cerr << "Error loading font\n";
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20); // Display in the top-left corner
    scoreText.setString("Score: " + std::to_string(score));


    // Initialize high score text
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(40);
    highScoreText.setFillColor(Color::Yellow);
    highScoreText.setPosition(20, 80);  // Positioned below the score
    highScoreText.setString("High Score: 0");

    //level text
    levelText.setFont(font);
    levelText.setCharacterSize(40);
    levelText.setFillColor(Color::White);
    levelText.setPosition(20, 140); // Position it below the score
    levelText.setString("Level: 1");

    //  Initialize OptionsScreen
    optionsScreen = new OptionsScreen(resolution.x, resolution.y);


}

engine::~engine() {
    delete optionsScreen;  // Prevent memory leaks
    optionsScreen = nullptr;
    // Added but need to test out.
    meteors.clear();
    c_Window.close();
}

void engine::start() {
    Clock clock;
    isMenuActive = true;
    isOptionsActive = false; // Initialize options menu as inactive

    while (c_Window.isOpen()) {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();

        if (isGameOver) {
            handleGameOver();
        }
        else if (isOptionsActive) { // Show options menu if active
            showOptions();
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
void engine::increaseScore(int value) {
    score += value;
    scoreText.setString("Score: " + std::to_string(score));
    // Check if the new score is the highest in the current session
    if (score >= scoreThreshold) {
        increaseLevel();
    }

    if (score > highestScore) {
        highestScore = score;
        highScoreText.setString("High Score: " + std::to_string(highestScore));
    }

}
void engine::resetScore() {
    score = 0;  // Reset score
    scoreText.setString("Score: 0");  // Update display text
}

void engine::resetLevel() {
    level = 0;  // Reset score
    levelText.setString("Level: 1");  // Update display text
}
void engine::resetGame() {
    meteors.clear();  // Remove all meteors
    inst_character = character(Vector2f(960.f + 85.0f, 540.f), texManager);  // Reset character position
    gamePaused = false;
    isGameOver = false;
    isMenuActive = false;  // Resume game from menu

    meteorSpawnClock.restart();  //  Restart meteor spawn timer
    resetScore(); 
    resetLevel();// Call the function to reset score
    level = 1; // Reset level
    // Reset Diff

    
    meteorSpeed = hardDifficulty ? 200.f : 100.f;
    meteorSpawnRate = hardDifficulty ? 1.25f : 2.5f;
    meteorBatchSize = hardDifficulty ? 2 : 1;

    c_Window.clear();
    draw();
    c_Window.display();
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

    if (gameOverClock.getElapsedTime().asSeconds() > 1.0f) {
        isGameOver = false;
        isMenuActive = true;
    }
}

TextureManager texManager;
void engine::spawnMeteor() {
    for (int i = 0; i < meteorBatchSize; i++) {
        float meteorX, meteorY;
        int edge = std::rand() % 4; // Pick a random edge (0: top, 1: bottom, 2: left, 3: right)

        if (edge == 0) {
            meteorX = static_cast<float>(std::rand() % c_Window.getSize().x);
            meteorY = -50.f;
        }
        else if (edge == 1) { 
            meteorX = static_cast<float>(std::rand() % c_Window.getSize().x);
            meteorY = c_Window.getSize().y + 50.f;
        }
        else if (edge == 2) { 
            meteorX = -50.f;
            meteorY = static_cast<float>(std::rand() % c_Window.getSize().y);
        }
        else { 
            meteorX = c_Window.getSize().x + 50.f; 
            meteorY = static_cast<float>(std::rand() % c_Window.getSize().y);
        }

        float meteorSize = static_cast<float>((std::rand() % 30) + 20); // Random size between 20-50

        meteors.emplace_back(Vector2f(meteorX, meteorY), meteorSize, texManager);
        meteors.back().setSpeed(meteorSpeed);
    }
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
            gameOverClock.restart();
            return true;
        }
    }
    return false;
}

void engine::showOptions() {
    bool inOptions = true;
    bool inMenu = false;
    bool easyModeSelected = false;
    bool hardModeSelected = false;

    while (inOptions && c_Window.isOpen()) {
        Event event;
        while (c_Window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                c_Window.close();
                return;
            }

            optionsScreen->handleEvent(event, c_Window, inOptions, inMenu, easyModeSelected, hardModeSelected);
        }

        c_Window.clear(Color::Black);
        optionsScreen->draw(c_Window);
        c_Window.display();

        // Ensure new game starts correctly when switching difficulty
        if (easyModeSelected) {
            resetGame();  //  Reset game to initial state
            setDifficulty(false); // Set difficulty to Easy
        }
        else if (hardModeSelected) {
            resetGame();  //  Reset game to initial state
            setDifficulty(true); // Set difficulty to Hard (increase speed)
        }

        if (!inOptions) {  // If "Back" is pressed, return to menu
            isOptionsActive = false;
            isMenuActive = true;  // Properly return to main menu
        }
    }

}
void engine::setDifficulty(bool hardMode) {
    meteorSpeed = hardMode ? 400.f : 200.f; 
    meteorSpawnRate = hardMode ? 1.25f : 2.5f;
    meteorBatchSize = hardMode ? 2 : 1; 

    // Apply speed to existing meteors
    for (auto& m : meteors) {
        m.setSpeed(meteorSpeed);
    }

    hardDifficulty = hardMode;
}


void engine::increaseLevel() {
    level++;
    std::cout << "LEVEL UP: LEVEL " << level << std::endl;
    levelText.setString("Level: " + std::to_string(level));
    if (hardDifficulty) {
        meteorSpeed += 50.f; 
        meteorSpawnRate *= 0.8f; 
        meteorBatchSize = std::min(meteorBatchSize + 1, 10); // prevents too much rocks caps at 10
    }
    else {
        meteorSpeed += 10.f;
        meteorSpawnRate *= 0.9f; 
        meteorBatchSize = std::min(meteorBatchSize + 1, 5);
    }


    scoreThreshold += 100;

}