#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "meteor.h"
#include "Menu.h"
#include "character.h"
#include "orbit.h"
#include "OptionsScreen.h"  // Include OptionsScreen

using namespace sf;

class engine {
private:
    RenderWindow c_Window;
    Menu menu;
    OptionsScreen* optionsScreen = nullptr;  // Use pointer for dynamic allocation
    bool isMenuActive = true;
    bool isGameOver = false;
    bool isOptionsActive = false;
    int gameOverSelection = 0;
    bool gamePaused = false;

    orbit inst_orbit = orbit(100.f, 5.f);
    character inst_character = character(Vector2f(960.f + 85.0f, 540.f));

    std::vector<meteor> meteors;
    Clock meteorSpawnClock;
    Clock gameOverClock;

    void spawnMeteor();
    void input();
    void update(float dtAsSeconds);
    void draw();
    void resetGame();
    void handleGameOver();
    bool checkCollision();
    void showOptions();  //  Function for Options menu
    int score = 0;
    int highestScore = 0;
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
    void resetScore();



public:
    engine();
    ~engine();  //  Destructor for memory cleanup
    void start();
    void increaseScore(int value);

};
