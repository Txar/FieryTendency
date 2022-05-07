#include "SFML/Graphics.hpp"
#include "game/World/Tile.hpp"
#include <algorithm>
#pragma once

struct TrailPoint {
    int x;
    int y;
    float timer;
};

struct Bullet {
    int piercing = 0;
    float damage = 5;
    int bounces = 0;
    int height;
    int width;
    int team = 0; //0 is player, 1 is enemies, 2 is both
    sf::Vector2i spriteOffset;
    float speed = 20;
    sf::IntRect sprite = {0, 0, TILE_SIZE, TILE_SIZE};
};

sf::Vector2f shootBullet(sf::Vector2i mousepos, sf::Vector2f source, sf::Vector2i camera, sf::Vector2i resolution, Bullet bullet){
    sf::Vector2f velocity;
    sf::Vector2f endVelocity;
    
    float x = (mousepos.x - resolution.x / 2);
    float y = (mousepos.y - resolution.y / 2);
    
    std::cout << "x " << (camera.x - source.x) << " y " << (camera.y - source.y) << std::endl;
    float mouserelation = std::max(abs(x), abs(y));

    velocity.x = (float)(x) / mouserelation;
    velocity.y = (float)(y) / mouserelation;

    float speed = bullet.speed;

    endVelocity.x = bullet.speed / 2 * velocity.x;
    speed -= bullet.speed / 2 * abs(velocity.x);

    endVelocity.y = bullet.speed / 2 * velocity.y;
    speed -= bullet.speed / 2 * abs(velocity.y);

    if (speed > 0){
        if (abs(velocity.x) > abs(velocity.y)){
            endVelocity.x += speed * velocity.x;
        }
        else {
            endVelocity.y += speed * velocity.y;
        }
    }

    return endVelocity;
}