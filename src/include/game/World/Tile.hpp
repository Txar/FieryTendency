#include "SFML/Graphics.hpp"
#include <math.h>
#pragma once

const int TILE_SIZE = 16;

int SnapToTileGrid(float s){
    return TILE_SIZE * ceil(s / TILE_SIZE);
};

struct Tile {
    public:
        bool solid = false;
        bool reflecting = false;
        bool floor = false;
        int sprite;
        float friction = 0.4;
        int id;
};