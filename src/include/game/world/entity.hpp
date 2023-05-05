#include "SFML/Graphics.hpp"
#include "game/graphics/animator.hpp"

#pragma once

class entity {
    public:
        entity(std::string name, int _width, int _height, float weight = 1) {
            animators.push_back(animator(name));
            width = _width;
            height = _height;
            x = 0;
            y = 0;
        }

        ~entity() {

        }

        virtual void update(float delta_time) {
            for (animator i : animators) i.update(delta_time);
            //std::cout << velocity.x * delta_time << std::endl;
        }

        void applyForce(sf::Vector2f force) {
            velocity += force;
        }

        void summon(float _x, float _y) { //, int _width, int _height) {
            x = _x;
            y = _y;
            alive = true;
            //width = _width;
            //height = _height;
        }

        sf::Sprite draw() {
            sf::RenderTexture rt;
            rt.create(width, height);
            rt.clear(sf::Color(0, 0, 0, 0));
            for (animator i : animators) {
                rt.draw(i.getSprite());
            }
            rt.display();
            t = rt.getTexture();
            sf::Sprite s(t);
            s.setPosition({x, y});
            return s;
        }

        sf::Vector2f velocity = {0.0, 0.0};
        int width, height;
        float x, y;
        float mass;
        bool alive;
        bool grounded = false;
        std::vector<std::pair<sf::IntRect, bool>> colliders; //the bool is saying whether it's colliding with something or not
        std::vector<std::pair<sf::IntRect, bool>> damageColliders; //same here
        bool applyGravity = true, applyFriction = true;

    private:
        sf::Texture t;
        std::vector<animator> animators;
};

namespace wrld {
    float camera_x = 0;
    float camera_y = 0;
    sf::Vector2f camera_center;

    const float G = 10.0;
    const float FRICTION_COEFFICIENT_NORMAL = 0.7;
}