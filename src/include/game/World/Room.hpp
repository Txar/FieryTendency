#include "game/World/TileSet.hpp"
#include "game/Content/WorldProperties.hpp"
#pragma once

struct Room {
        bool connections[4]; //{top, right, bottom, left}
        int tiles[WORLD_LAYERS][ROOM_WIDTH][ROOM_HEIGHT];
    };

        