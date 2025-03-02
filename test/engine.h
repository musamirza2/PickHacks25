#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "meteor.h"
#include "Menu.h"
#include "character.h"
#include "background.h"
#include "orbit.h"
#include "OptionsScreen.h"  // Include OptionsScreen

using namespace sf;

class engine {
private:
    TextureManager texManager;
    RenderWindow c_Window;
    Menu menu;
    Background background;
    OptionsScreen* optionsScreen = nullptr;  // Use pointer for dynamic allocation
    bool isMenuActive = true;
    bool isGameOver = false;
    float meteorSpawnRate =100.5f; 
    int meteorBatchSize = 1;
    bool isOptionsActive = false;
    int gameOverSelection = 0;
    bool gamePaused = false;
    float meteorSpeed = 200.f; //  Default speed for Easy mode
    std::vector<meteor> meteors;


    orbit inst_orbit = orbit(100.f, 5.f);
    character inst_character = character(Vector2f(960.f + 85.0f, 540.f), texManager);

 
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
    bool hardDifficulty;
    int level = 1; // Current game level
    int scoreThreshold = 100;
    Text levelText;
    void increaseLevel();
    void resetLevel();

public:
    engine();
    ~engine();  //  Destructor for Memory 
    void start();
    void increaseScore(int value);
    void setDifficulty(bool hardMode);
};
