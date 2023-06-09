#include <iostream>
#include <cmath>
#include <algorithm>
#include "graphics/screen_manager.hpp"
#include "world/player_entity.hpp"
#include "world/block.hpp"
#include "content/entity_manager.hpp"
#include "world/world.hpp"

#pragma once

class game {
    private:
        float delta_time;
        int fps = 0;
        int frame = 0;
        bool debug;

        screen_manager screen_mgr;

        world w;
    
    public:
        game(bool _debug = false) : screen_mgr("Fiery Tendency", 1280, 720){
            debug = _debug;
        }
        
        int main_loop() {
            bool running = true;

            kb::new_bind(sf::Keyboard::A, "move_left");
            kb::new_bind(sf::Keyboard::D, "move_right");
            kb::new_bind(sf::Keyboard::Space, "jump");

            sf::Clock clock;
            float second_timer = 0;

            while (running) {
                delta_time = clock.restart().asSeconds();
                second_timer += delta_time;
                if (second_timer >= 1) {
                    second_timer = 0;
                    fps = frame;
                    wrld::fps = fps;
                    std::cout << fps << " fps" << std::endl;
                    frame = 0;
                }
                frame++;

                bool draw_colliders = true;

                em::updateGlobalEvents();

                w.update(delta_time, fps);

                screen_mgr.clear();

                screen_mgr.draw_blocks(w.block_mgr.tilemap); //needs optimization obviously
                screen_mgr.drawEntities(&w.alive_entity_mgr.entities, draw_colliders);

                w.resetCamera();
                
                srvr::eventPool.flush();
                running = screen_mgr.update();
            }
            return 0;
        }
};