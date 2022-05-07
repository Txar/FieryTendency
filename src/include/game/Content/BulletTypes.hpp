#include <vector>
#include "game/Weapon/Bullet.hpp"
#include "SFML/Graphics.hpp"
#pragma once

std::vector<Bullet> bulletTypes;
sf::Texture bulletTexture;

void LoadBullets(){
    bulletTexture.loadFromFile("assets/bullets.png");
    Bullet tempBullet;

    tempBullet.speed = 8;
    tempBullet.damage = 3;
    tempBullet.piercing = 0;
    tempBullet.sprite = {0, 0, 4, 4};
    tempBullet.width = 4;
    tempBullet.height = 4;
    tempBullet.bounces = 0;
    tempBullet.team = 0;
    bulletTypes.push_back(tempBullet);
};