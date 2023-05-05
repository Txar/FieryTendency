#include "SFML/Graphics.hpp"
#include "game/graphics/animator.hpp"

#pragma once

class block {
    public:
        bool visible = true;
        bool solid = true;

        block(std::string name = "none") : anim(name) {
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

    private:
        animator anim;
        std::string name;
        std::vector<sf::IntRect> collider;
};

namespace wrld {
    const int BLOCK_SIZE = 64;

    const int WORLD_WIDTH = 128;
    const int WORLD_HEIGHT = 128;
}