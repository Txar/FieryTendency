#include "game/world/animated_block.hpp"

#pragma once

class block_manager {
    public:
        std::map<std::string, block> blocks;
        block ***tilemap;
        block none;

        bool add_block(block *b) {
            if (exists(b->name)) return false;
            else blocks.insert({b->name, *b});
            return true;
        }

        bool exists(std::string name) {
            return (blocks.find(name) != blocks.end());
        }

        block get(std::string name) {
            if (!exists(name)) return none;
            else return (blocks[name]);
        }

        block *get_ptr(std::string name) {
            if (!exists(name)) return &none;
            else return &(blocks[name]);
        }

        block_manager(bool load = false) {
            tilemap = new block **[wrld::WORLD_WIDTH];
            if (load) {
                block test_block("test_anim");
                test_block.anim.animated = true;
                test_block.anim.frames = 4;
                test_block.anim.speed = 8.0;
                test_block.anim.height = 64;
                test_block.anim.width = 64;
                test_block.anim.pingpong = false;
                add_block(&test_block);
                for (int i = 0; i < wrld::WORLD_WIDTH; i++) {
                    tilemap[i] = new block *[wrld::WORLD_HEIGHT];
                    for (int j = 0; j < wrld::WORLD_HEIGHT; j++) {
                        tilemap[i][j] = &none;
                        if (i == 0 || j == 5 || (j == 2 && i > 7)) {
                            tilemap[i][j] = get_ptr("test_anim");
                        }
                    }
                }
            }
        }

        bool is_solid(int x, int y) {
            return tilemap[x][y]->solid;
        }

        void update(float delta_time) {
            for (auto i : blocks) {
                blocks[i.first].update(delta_time);
            }
        }
};

namespace wrld {
    //block_manager block_mgr(true);
}