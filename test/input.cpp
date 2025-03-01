#include "engine.h"

using namespace sf;

void engine::input() {

    //esc will close window
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        c_Window.close();
    }

    // Handle the player moving
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        inst_character.moveLeft();
    }
    else
    {
        inst_character.stopLeft();
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        inst_character.moveRight();
    }
    else
    {
        inst_character.stopRight();
    }
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        inst_character.moveUp();
    }
    else
    {
        inst_character.stopUp();
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        inst_character.moveDown();
    }
    else
    {
        inst_character.stopDown();
    }
}
