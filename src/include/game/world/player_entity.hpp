#include "box_entity.hpp"
#include "game/io/events.hpp"
#include <iostream>
#include <cmath>

#pragma once

class player_entity : public box_entity {
    public:
        bool holdingJump = false, justJumped = false;
        float jumpLoad = 1.0;
        float maxJumpTime = 0.06;
        float jumpVelocity = wrld::BLOCK_SIZE * 16;
        float maxRunningVelocity = wrld::BLOCK_SIZE * 20;
        float runningAcceleration = wrld::BLOCK_SIZE;

        player_entity(std::string name, int _width, int _height) : box_entity {name, _width, _height} {
            colliders = {
                {{0, 8, 8, height - 16}, false}, //left
                {{width - 8, 8, 8, height - 16}, false}, //right
                {{8, 0, width - 16, 8}, false}, //top
                {{8, height, width - 16, 8}, false} //bottom
            };
            mass = 2.0;
        };

        void update(float delta_time) {
            box_entity::update(delta_time);

            if (abs(velocity.x) < maxRunningVelocity) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) applyForce({runningAcceleration, 0});
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) applyForce({-runningAcceleration, 0});
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !justJumped && bottomCollider) {
                holdingJump = true;
                justJumped = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (holdingJump && jumpLoad > 0.0) {
                    applyForce({0, -jumpVelocity * float(sin(jumpLoad * 1.57) * delta_time / 2)});
                    jumpLoad -= (1.0 / maxJumpTime) * delta_time;
                }
            }
            else holdingJump = false;
            if (bottomCollider && jumpLoad < 1.0 && !holdingJump) {
                justJumped = false;
                jumpLoad = 1.0;
            }
        }
};