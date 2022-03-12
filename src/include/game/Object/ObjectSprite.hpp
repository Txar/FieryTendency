#include "SFML/Graphics.hpp"
#pragma once

struct ObjectSprite {
    sf::Vector2i offset = {0, 0};
    sf::Sprite sprite;
};