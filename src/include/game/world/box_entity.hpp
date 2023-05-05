#include "block.hpp"
#include "entity.hpp"
#include "game/io/events.hpp"
#include <cmath>
#include <iostream>

#pragma once

class box_entity : public entity {
    private:
        void applyMovement(float delta_time) {
            if (fabs(velocity.x) < 20.0) velocity.x = 0.0;
            
            if (velocity.x < 0.0) {
                if (bottomCollider) applyForce({wrld::FRICTION_COEFFICIENT_NORMAL * mass * wrld::G, 0});
                if (!leftCollider) x += velocity.x * delta_time;
                else velocity.x = 0;
            }
            if (velocity.x > 0.0) {
                if (bottomCollider) applyForce({-wrld::FRICTION_COEFFICIENT_NORMAL * mass * wrld::G, 0});
                if (!rightCollider) x += velocity.x * delta_time;
                else velocity.x = 0;
            }
            if (velocity.y < 0.0) {
                if (!topCollider) y += velocity.y * delta_time;
                else velocity.y = 0;
            }
            if (velocity.y > 0.0) {
                if (!bottomCollider) y += velocity.y * delta_time;
                else velocity.y = 0;
            }
        }

    public:
        bool leftCollider, rightCollider, topCollider, bottomCollider;

        box_entity(std::string name, int _width, int _height) : entity {name, _width, _height} {
            colliders = {
                {{0, 8, 8, height - 16}, false}, //left
                {{width - 8, 8, 8, height - 16}, false}, //right
                {{8, 0, width - 16, 8}, false}, //top
                {{8, height, width - 16, 8}, false} //bottom
            };
            mass = 2.0;
        };

        void update(float delta_time) {
            entity::update(delta_time);

            leftCollider = colliders.at(0).second;
            rightCollider = colliders.at(1).second;
            topCollider = colliders.at(2).second;
            bottomCollider = colliders.at(3).second;

            applyMovement(delta_time);

            if (applyGravity) applyForce({0, wrld::G * mass});
        }
};