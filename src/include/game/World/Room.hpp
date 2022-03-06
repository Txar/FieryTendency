#include "game/World/TileSet.hpp"
#pragma once

struct Room {
        bool connections[4]; //{top, right, bottom, left}
        int tiles[20][12];
    };

        