#include "game/world/animated_block.hpp"

#pragma once

class block_manager {
    public:
        std::map<std::string, block*> blocks;
        block none;

        block_manager(bool load) {
            if (load) {
                
            }
        }

        bool addBlock(block *b) {
            if (exists((*b).name)) return true;
            else blocks.insert({(*b).name, b});
        }

        bool exists(std::string name) {
            return (blocks.find(name) != blocks.end());
        }

        block get(std::string name) {
            if (!exists(name)) return none;
            else return (*blocks[name]);
        }
};

namespace wrld {
    block_manager block_mgr(true);
}