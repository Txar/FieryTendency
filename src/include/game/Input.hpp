#include "SFML/Window/Keyboard.hpp"
//#include <math.h>
#pragma once

bool SpacePressed = false;
bool FPressed = false;

sf::Vector2i mouse;

void MoveKeyInput(float movement[2]){
    SpacePressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        SpacePressed = true;
    }
    FPressed = false;
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::F))){
        FPressed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        movement[1]--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        movement[0]--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        movement[1]++;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        movement[0]++;
    }

    /*
    if (abs(movement[0]) == abs(movement[1])){
        movement[0] = movement[0] / 2;
        movement[1] = movement[1] / 2;
    }*/
}