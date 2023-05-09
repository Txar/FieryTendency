#include <iostream>
#include <cmath>
#include <algorithm>
#include "graphics/screen_manager.hpp"
#include "world/player_entity.hpp"
#include "world/block.hpp"
#include "content/entity_manager.hpp"
#include <windows.h>

#pragma once

class game {
    private:
        float delta_time;
        int fps = 0;
        int frame = 0;
        entity_manager alive_entity_mgr;

        screen_manager screen_mgr;
        block **block_map;

        int customRound(int x, int base = wrld::BLOCK_SIZE) {
            return int(base * ceil(float(x) / base) - base);
        }

        bool isInBounds(int x, int y) {
            return isInBounds(int(customRound(x) / wrld::BLOCK_SIZE), int(customRound(y) / wrld::BLOCK_SIZE));
        }

        bool isInBoundsTile(int x, int y) {
            return (x < wrld::WORLD_WIDTH * wrld::BLOCK_SIZE && x >= 0
                && y < wrld::WORLD_HEIGHT * wrld::BLOCK_SIZE && y >= 0);
        }

        sf::IntRect blockCollider(int x, int y) {
            return blockCollider(int(customRound(x) / wrld::BLOCK_SIZE), int(customRound(y) / wrld::BLOCK_SIZE));
        }

        sf::IntRect blockColliderTile(int x, int y) {
            return sf::IntRect(x * wrld::BLOCK_SIZE, y * wrld::BLOCK_SIZE, 
            wrld::BLOCK_SIZE, wrld::BLOCK_SIZE);
        }

        std::vector<sf::IntRect> surroundingBlockColliders(int x, int y, int radius = 3) {
            return surroundingBlocksColiidersTile(int(customRound(x) / wrld::BLOCK_SIZE), int(customRound(y) / wrld::BLOCK_SIZE), radius);
        }

        std::vector<sf::IntRect> surroundingBlocksColiidersTile(int x, int y, int radius = 3) {
            std::vector<sf::IntRect> colliders;
            for (int i = x - radius; i < x + radius; i++) {
                if (!isInBoundsTile(i, 0)) continue;
                for (int j = y - radius; j < y + radius; j++) {
                    if (!isInBoundsTile(0, j)) continue;
                    if (block_map[i][j].solid) {
                        colliders.push_back(blockColliderTile(i, j));
                    }
                }
            }
            return colliders;
        }

        void checkEntityColliders(entity *e) {
            std::vector<sf::IntRect> colliders = surroundingBlockColliders((*e).x, (*e).y);
            for (int i = 0; i < int((*e).colliders.size()); i++) {
                sf::IntRect c = (*e).colliders.at(i).first;
                c.left += (*e).x;
                c.top += (*e).y;
                (*e).colliders.at(i).second = false;
                for (sf::IntRect j : colliders) {
                    if (c.intersects(j)) {
                        (*e).colliders.at(i).second = true;
                        break;
                    }
                }
            }
        }
    
    public:
        game() : screen_mgr("Fiery Tendency", 1280, 720){
            
        }
        
        int main_loop() {
            bool running = true;

            block test_block("test_anim");
            test_block.anim.animated = true;
            test_block.anim.frames = 4;
            test_block.anim.speed = 8.0;
            test_block.anim.height = 64;
            test_block.anim.width = 64;
            test_block.anim.pingpong = false;

            block_map = new block* [wrld::WORLD_WIDTH];
            for (int i = 0; i < wrld::WORLD_WIDTH; i++) {
                block_map[i] = new block[wrld::WORLD_HEIGHT];
                for (int j = 0; j < wrld::WORLD_HEIGHT; j++) {
                    block_map[i][j] = block();
                    if (i == 0 || j == 5 || (j == 2 && i > 7)) {
                        block_map[i][j] = test_block;
                    }
                }
            }

            sf::Clock clock;
            float second_timer = 0;
            float sim_delta_time = 0.0;

            while (running) {
                wrld::camera_center = {float((*alive_entity_mgr.get_ptr("player1")).x), float((*alive_entity_mgr.get_ptr("player1")).y)};
                wrld::camera_x = wrld::camera_center.x;
                wrld::camera_y = wrld::camera_center.y;
                delta_time = clock.restart().asSeconds();
                second_timer += delta_time;
                if (second_timer >= 1) {
                    second_timer = 0;
                    sim_delta_time = 1.0 / frame;
                    fps = frame;
                    wrld::fps = fps;
                    std::cout << delta_time << std::endl;
                    std::cout << fps << " fps" << std::endl;
                    frame = 0;
                }
                frame++;

                bool draw_colliders = false;

                //delta_time = sim_delta_time;

                for (int i = 0; i < wrld::WORLD_WIDTH; i++) { 
                    for (int j = 0; j < wrld::WORLD_HEIGHT; j++) (block_map[i][j]).update(delta_time);
                }
                screen_mgr.clear();
                screen_mgr.drawBlocks(&block_map); //needs optimization obviously
                screen_mgr.drawEntities(&alive_entity_mgr.entities, draw_colliders);

                entity *e;
                while (alive_entity_mgr.iter(&e)) {
                    if (fps < 60) {
                        checkEntityColliders(e);
                        (*e).update(delta_time / 3);
                        checkEntityColliders(e);
                        (*e).update(delta_time / 3);
                        checkEntityColliders(e);
                        (*e).update(delta_time / 3);
                    }
                    else if (fps < 100) {
                        checkEntityColliders(e);
                        (*e).update(delta_time / 2);
                        checkEntityColliders(e);
                        (*e).update(delta_time / 2);
                    }
                    else {
                        checkEntityColliders(e);
                        (*e).update(delta_time);
                    }

                    running = screen_mgr.update();
                }
            }
            return 0;
        }
};