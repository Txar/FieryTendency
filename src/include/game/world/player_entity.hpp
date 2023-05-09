#include "box_entity.hpp"
#include "game/io/events.hpp"
#include "game/math/cap.hpp"
#include <iostream>
#include <cmath>

#pragma once

class player_entity : public box_entity {
    public:
        bool holdingJump = false, justJumped = false, running = false;
        bool facingLeft = false;
        float jumpLoad = 1.0;
        float maxJumpTime = 0.08;
        float jumpVelocity = 16.0;
        float maxRunningVelocity = 1.0;
        float runningAcceleration = 1.0;

        player_entity(entity &e) : box_entity{e} {

        }

        player_entity(std::string name, int _width, int _height, std::string _type = "player") : box_entity {name, _width, _height, _type} {
            animators.push_back(animator("none", width, height, 6));
            colliders = {
                {{0, 16, 8, height - 32}, false}, //left
                {{width - 8, 16, 8, height - 32}, false}, //right
                {{16, 0, width - 32, 8}, false}, //top
                {{16, height - 8, width - 32, 24}, false} //bottom
            };
            mass = 3.0;
            //applyFriction = false;
        };

        virtual void update(float delta_time) override {
            box_entity::update(delta_time);
            //std::cout << velocity.x << std::endl;
            if (abs(velocity.x) > 0.0) {
                animators.at(0).speed = capAt(std::fabs(velocity.x) * delta_time * 16, 8.0);
                //if (!bottomCollider) animators.at(0).speed = 0;
                running = true;
                if (velocity.x > 0.0) facingLeft = false;
                else facingLeft = true;
            }
            else {
                running = false;
            }

            animators.at(0).flipSprite = facingLeft;
            if (!bottomCollider) {
                animators.at(0).name = "Anastasia-Fall";
                animators.at(0).animated = false;
                animators.at(0).frame = 0;
            }
            else if (!running) {
                animators.at(0).name = "Anastasia-Stand";
                animators.at(0).animated = false;
                animators.at(0).frame = 0;
            }
            else {
                animators.at(0).name = "Anastasia-Run";
                animators.at(0).animated = true;
            }

            if (abs(velocity.x) < maxRunningVelocity * wrld::FORCE_MULTIPLIER) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) applyForce({runningAcceleration, 0}, delta_time);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) applyForce({-runningAcceleration, 0}, delta_time);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !justJumped && bottomCollider) {
                holdingJump = true;
                justJumped = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (holdingJump && jumpLoad > 0.0) {
                    applyForce({0, -jumpVelocity}, delta_time);
                    jumpLoad -= (1.0 / maxJumpTime) * delta_time;
                }
            }
            else holdingJump = false;
            if (bottomCollider && jumpLoad < 1.0 && !holdingJump) {
                justJumped = false;
                jumpLoad = 1.0;
            }

            applyMovement(delta_time);
        }
};