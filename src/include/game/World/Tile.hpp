#include "SFML/Graphics.hpp"
#include <math.h>
#pragma once

const int TILE_SIZE = 64;

int SnapToTileGrid(float s){
    return TILE_SIZE * ceil(s / TILE_SIZE);
};

struct Tile {
    public:
        bool solid = false;
        int sprite;
        int id;
};