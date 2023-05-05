#include "SFML/Graphics.hpp"

#pragma once

namespace em { //so called "event manager"
    std::vector<sf::Event> events;

    void update(sf::RenderWindow * window) {
        sf::Event event;
        events.clear();
        while ((*window).pollEvent(event)){
            events.push_back(event);
        }
    }
}