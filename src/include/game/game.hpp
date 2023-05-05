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

        void moveEntity(entity *e) {
            std::vector<sf::IntRect> colliders = surroundingBlockColliders((*e).x, (*e).y);
            //std::cout << colliders.size() << std::endl;
            bool collides_x = false;
            bool collides_y = false;
            float vel = std::max((*e).velocity.x, (*e).velocity.y);
            float div = 1;
            if (vel > wrld::BLOCK_SIZE / 4) {
                div = vel / (wrld::WORLD_WIDTH / 4); // v / div = small_v
            }                                        // small_v * div = v
                                                     // v/small_v = div
            for (int d = 0; d < div; d++) {
                for (std::pair<sf::IntRect, bool> i : (*e).colliders) {
                    sf::IntRect c = i.first;
                    c.left += (*e).x;
                    c.top += (*e).y;
                    if (i.second) continue;
                    for (sf::IntRect j : colliders) {
                        if (!collides_x) {
                            c.left += (*e).velocity.x / div * delta_time;
                            if (c.intersects(j)) {
                                if (!((*e).velocity.x < 0 && j.left > c.left)
                                 && !((*e).velocity.x > 0 && j.left < c.left)) {
                                    collides_x = true;
                                }
                            }
                            c.left -= (*e).velocity.x / div * delta_time;
                        }
                        if (!collides_y) {
                            c.top += (*e).velocity.y / div * delta_time;
                            if (c.intersects(j)) {
                                collides_y = true;
                            }
                            c.top -= (*e).velocity.y / div * delta_time;
                        }
                        if (collides_x && collides_y) break;
                    }
                    if (collides_x && collides_y) break;
                }
                if (!collides_x) {
                    (*e).x += (*e).velocity.x / div * delta_time;
                }
                else {
                    (*e).velocity.x = 0;
                }

                (*e).grounded = false;
                if (!collides_y) {
                    (*e).y += (*e).velocity.y / div * delta_time;
                }
                else if ((*e).velocity.x < 0) {
                    (*e).grounded = true;
                }
                if (collides_y) {
                    (*e).velocity.y = 0;
                }
                if (collides_x && collides_y) break;
            }
        }
    
    public:
        game() : screen_mgr("Fiery Tendency", 800, 600){
            
        }
        
        int main_loop() {
            bool running = true;
            player_entity player(std::string("player"), 128, 128);
            player.colliders.push_back({sf::IntRect(16, 16, 96, 96), false});
            entity_map.push_back(&player);
            player.x = 512;
            player.y = 128;

            block_map = new block* [wrld::WORLD_WIDTH];
            for (int i = 0; i < wrld::WORLD_WIDTH; i++) {
                block_map[i] = new block[wrld::WORLD_HEIGHT];
                for (int j = 0; j < wrld::WORLD_HEIGHT; j++) {
                    block_map[i][j] = block();
                    if (i == 0 || j == 5) {
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
                delta_time = clock.getElapsedTime().asSeconds();
                clock.restart();
                secondTimer += delta_time;
                if (secondTimer >= 1) {
                    secondTimer = 0;
                    std::cout << fps << " fps" << std::endl;
                    fps = 0;
                }
                fps++;

                for (int i = 0; i < int(entity_map.size()); i++) {
                    (*entity_map.at(i)).update();
                    moveEntity(entity_map.at(i));
                }

                for (int i = 0; i < wrld::WORLD_WIDTH; i++) { 
                    for (int j = 0; j < wrld::WORLD_HEIGHT; j++) (block_map[i][j]).update();
                }
                screen_mgr.clear();
                screen_mgr.drawBlocks(&block_map); //needs optimization obviously
                screen_mgr.drawEntities(&entity_map);
                running = screen_mgr.update();
            }
            return 0;
        }
};