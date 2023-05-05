#include "SFML/Graphics.hpp"
#include "texture_manager.hpp"

#pragma once

class animator {
    public:
        std::string name;
        int frame = 0;
        int frames;
        float speed;
        bool pingpong;
        bool animated;
        int width;
        int height;
        float progress = 0;
        bool reverse = false;

        animator(std::string _name) {
            name = _name;
            animated = false;
        }

        animator(std::string _name, int _width, int _height, int amount_of_frames, float _speed = 1.0, bool _pingpong = false) {
            name = _name;
            frames = amount_of_frames;
            speed = _speed;
            pingpong = _pingpong;
            animated = true;
            width = _width;
            height = _height;
        }

        void update(float delta_time) {
            if (animated) {
                progress += delta_time;
                if (progress >= 1.0) {
                    progress = progress - 1.0;
                    if (frame == frames) {
                        if (pingpong) {
                            reverse = true;
                            frame--;
                        }
                        else {
                            frame = 0;
                        }
                    }
                    else if (frame == 0) {
                        reverse = false;
                        frame++;
                    }
                    else {
                        if (pingpong) frame = (reverse) ? frame - 1 : frame + 1;
                        else frame++;
                    }
                }
            }
        }

        sf::Sprite getSprite() {
            if (animated) {
                return texture_mgr.get_sprite(name, frame, width, height);
            }
            else {
                return texture_mgr.get_sprite(name);
            }
        }
};