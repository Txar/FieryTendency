#include "SFML/Graphics.hpp"
#include "game/Weapon/Weapon.hpp"
#pragma once

struct Item {
    sf::Sprite sprite;
    std::string name;
    std::string description;
    
    bool isWeapon = false;
    Weapon weapon;
};