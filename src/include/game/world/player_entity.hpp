#include "Entity.hpp"
#include "game/io/events.hpp"
#include <iostream>

#pragma once

class player_entity : public entity {
    public:
        player_entity(std::string name, int _width, int _height) : entity {name, _width, _height} {};

        void update() {
            entity::update();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (velocity.x < wrld::BLOCK_SIZE * 4 * 60) applyForce({20, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (velocity.x > -wrld::BLOCK_SIZE * 4 * 60) applyForce({-20, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                applyForce({0, 20});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                applyForce({0, -20});
            }
        }
};