#include "game/world/player_entity.hpp"

#pragma once

namespace em {
    
}

class entity_manager {
    public:
        std::map<std::string, entity> base_entities;
        std::map<std::string, box_entity> box_entities;
        std::map<std::string, player_entity> player_entities;
        std::vector<entity*> entities;
        entity none = entity("none", 0.0, 0.0, 0.0);
        int iterator = 0;

        bool iter(entity **e) {
            if (iterator == int(entities.size())) {
                iterator = 0;
                return false;
            }
            else {
                iterator++;
                (*e) = entities[iterator];
                return true;
            }
        }

        void update(float delta_time) {
            for (auto i : base_entities) base_entities[i.first].update(delta_time);
            for (auto i : box_entities) box_entities[i.first].update(delta_time);
            for (auto i : player_entities) player_entities[i.first].update(delta_time);
        }

        bool addEntity(entity *e) {
            if (exists((*e).name)) return true;
            if ((*e).type == "baseEntity") {
                base_entities.insert({(*e).name, *e});
                entities.push_back(&base_entities[(*e).name]);
            }
            else if ((*e).type == "boxEntity") {
                box_entities.insert({(*e).name, box_entity(*e)});
                entities.push_back(&box_entities[(*e).name]);
            }
            else if ((*e).type == "playerEntity") {
                player_entities.insert({(*e).name, player_entity(*e)});
                entities.push_back(&player_entities[(*e).name]);
            }
            return false;
        }

        bool exists(std::string name) {
            bool e = (base_entities.find(name) != base_entities.end())
             || (box_entities.find(name) != box_entities.end())
             || (player_entities.find(name) != player_entities.end());
            return e;
        }

        std::string type(std::string name) {
            if (base_entities.find(name) != base_entities.end()) return "baseEntity";
            if (box_entities.find(name) != box_entities.end()) return "boxEntity";
            if (player_entities.find(name) != player_entities.end()) return "playerEntity";
            else return "none";
        }

        entity *get_ptr(std::string name) {
            std::string t = type(name);
            if (t == "baseEntity") return &base_entities[name];
            if (t == "boxEntity") return &box_entities[name];
            if (t == "playerEntity") return &player_entities[name];
            else return &none;
        }

        entity_manager(bool load = true) {
            if (load) {
                player_entity p = player_entity("player1", 128, 128);
                addEntity(&p);
            }
        }
};

namespace wrld {
    entity_manager entity_mgr(true);
}