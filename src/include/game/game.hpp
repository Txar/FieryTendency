#include <iostream>
#include <cmath>
#include <algorithm>
#include "graphics/screen_manager.hpp"
#include "world/player_entity.hpp"
#include "world/block.hpp"

#pragma once

class game {
    private:
        float delta_time;
        int fps = 0;
        screen_manager screen_mgr;
        std::vector<entity*> entity_map;
        block **block_map;

        int customRound(int x, int base = wrld::BLOCK_SIZE) {
            return int(base * ceil(float(x) / base) - base);
        }

        bool isInBounds(int x, int y) {
            return isInBounds(int(customRound(x) / wrld::BLOCK_SIZE), int(customRound(y) / wrld::BLOCK_SIZE));
        }

        bool isInBoundsTile(int x, int y) {
            return (x <= wrld::WORLD_WIDTH * wrld::BLOCK_SIZE && x >= 0
                && y <= wrld::WORLD_HEIGHT * wrld::BLOCK_SIZE && y >= 0);
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
                sf::RectangleShape s({float(c.width), float(c.height)});
                s.setPosition(c.left, c.top);
                s.setFillColor(sf::Color(0, 0, 0, 0));
                s.setOutlineColor(sf::Color(255, 0, 0));
                s.setOutlineThickness(1.0);
                screen_mgr.window.draw(s);
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
            player_entity player(std::string("player"), 128, 128);
            entity_map.push_back(&player);
            player.x = 512;
            player.y = 128;

            block_map = new block* [wrld::WORLD_WIDTH];
            for (int i = 0; i < wrld::WORLD_WIDTH; i++) {
                block_map[i] = new block[wrld::WORLD_HEIGHT];
                for (int j = 0; j < wrld::WORLD_HEIGHT; j++) {
                    block_map[i][j] = block();
                    if (i == 0 || j == 5 || (j == 2 && i > 7)) {
                        block_map[i][j] = block("block");
                    }
                }
            }

            sf::Clock clock;
            float secondTimer = 0;

            while (running) {
                wrld::camera_center = {float(player.x), float(player.y)};
                wrld::camera_x = player.x;
                wrld::camera_y = player.y;
                delta_time = clock.restart().asSeconds();
                secondTimer += delta_time;
                if (secondTimer >= 1) {
                    secondTimer = 0;
                    std::cout << fps << " fps" << std::endl;
                    fps = 0;
                }
                fps++;

                for (int i = 0; i < wrld::WORLD_WIDTH; i++) { 
                    for (int j = 0; j < wrld::WORLD_HEIGHT; j++) (block_map[i][j]).update(delta_time);
                }
                screen_mgr.clear();
                screen_mgr.drawBlocks(&block_map); //needs optimization obviously
                screen_mgr.drawEntities(&entity_map);

                for (int i = 0; i < int(entity_map.size()); i++) {
                    (*entity_map.at(i)).update(delta_time);
                    checkEntityColliders(entity_map.at(i));
                }

                running = screen_mgr.update();
            }
            return 0;
        }
};