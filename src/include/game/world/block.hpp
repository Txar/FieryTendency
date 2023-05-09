#include "SFML/Graphics.hpp"
#include "game/graphics/animator.hpp"

#pragma once

class block {
    public:
        bool visible = true, solid = true;
        std::string name;
        animator anim;

        block(std::string _name = "none") : anim(_name) {
            name = _name;
            if (name == "none") {
                visible = false;
                solid = false;
            }
        }

        void update(float delta_time) {
            if (visible) anim.update(delta_time);
        }

        sf::Sprite draw() {
            return anim.getSprite();
        }

    protected:
        std::vector<sf::IntRect> collider;
};

namespace wrld {
    const int BLOCK_SIZE = 64;

    const int WORLD_WIDTH = 128;
    const int WORLD_HEIGHT = 128;
}