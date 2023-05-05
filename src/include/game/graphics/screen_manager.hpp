#include "SFML/graphics.hpp"
#include "game/io/events.hpp"
#include "game/world/entity.hpp"
#include "game/world/block.hpp"
#include <iostream>

#pragma once

class screen_manager {
    private:
        int screen_height, screen_width;
        sf::RenderWindow window;
        sf::View camera;

    public:
        screen_manager(std::string title, int _screen_width, int _screen_height) : window(sf::VideoMode(_screen_width, _screen_height), title) {
            screen_width = _screen_width;
            screen_height = _screen_height;
        }

        ~screen_manager() {
            window.close();
        }

        void drawEntities(std::vector<entity*> *entities) {
            sf::RenderTexture entity_buffer;
            entity_buffer.create(screen_width, screen_height);
            entity_buffer.clear(sf::Color(0, 0, 0, 0));
            for (entity * i : *entities) {
                sf::Sprite s = (*i).draw();
                s.setPosition(sf::Vector2f(s.getPosition().x - float(wrld::camera_x + 64 - screen_width/2), 
                                           s.getPosition().y - float(wrld::camera_y + 64 - screen_height/2)));
                entity_buffer.draw(s);
            }
            entity_buffer.display();
            sf::Sprite s(entity_buffer.getTexture());
            s.setPosition(float(wrld::camera_x + 64 - screen_width/2), float(wrld::camera_y + 64 - screen_height/2));
            window.draw(s);
        }

        void drawBlocks(block ***blocks) {
            sf::RenderTexture blocks_buffer;
            blocks_buffer.create(screen_width, screen_height);
            blocks_buffer.clear(sf::Color(0, 0, 0, 0));

            for (int i = 0; i < wrld::WORLD_WIDTH; i++) { 
                for (int j = 0; j < wrld::WORLD_HEIGHT; j++) {
                    //std::cout << i << " " << j << std::endl;
                    if (!(*blocks)[i][j].visible) continue;
                    sf::Sprite s = (*blocks)[i][j].draw();
                    //s.setPosition(sf::Vector2f(i * wrld::BLOCK_SIZE + window.getView().getViewport().left, j * wrld::BLOCK_SIZE + window.getView().getViewport().top));
                    s.setPosition(sf::Vector2f(i * wrld::BLOCK_SIZE - float(wrld::camera_x + 64 - screen_width/2),
                                               j * wrld::BLOCK_SIZE - float(wrld::camera_y + 64 - screen_height/2)));
                    blocks_buffer.draw(s);
                }
            }
            blocks_buffer.display();
            sf::Sprite s(blocks_buffer.getTexture());
            s.setPosition(float(wrld::camera_x + 64 - screen_width/2), float(wrld::camera_y + 64 - screen_height/2));
            window.draw(s);
        }

        void clear() {
            window.clear(sf::Color(0, 0, 0));
        }

        bool update() {
            camera.reset({float(wrld::camera_x + 64 - screen_width/2), float(wrld::camera_y + 64 - screen_height/2), float(screen_width), float(screen_height)}); // wrld::camera_center, {float(screen_width), float(screen_height)}
            window.setView(camera);
            em::update(&window);
            for (sf::Event i : em::events) {
                if (i.type == sf::Event::EventType::Closed) {
                    return false;
                }
            }
            window.display();
            return true;
        }
};