#include "SFML/Window/Keyboard.hpp"
#pragma once

void MoveKeyInput(int movement[2]){
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
}