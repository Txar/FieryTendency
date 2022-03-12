#include "game/World/Room.hpp"
#include <fstream>
#include <iostream>

void ExportRoomTo(Room room, std::string path){
    std::ofstream f;
    f.open(path);
    for (int layer = 0; layer < WORLD_LAYERS; layer++){
        for (int i = 0; i < ROOM_WIDTH; i++){
            for (int j = 0; j < ROOM_HEIGHT; j++){
                f << room.tiles[layer][i][j] << std::endl;
            }
        }
    }
    f << room.connections[0] << std::endl;
    f << room.connections[1] << std::endl;
    f << room.connections[2] << std::endl;
    f << room.connections[3];
    f.close();
}

Room LoadRoomFrom(std::string path){
    std::ifstream f;
    f.open(path);
    Room a;
    for (int layer = 0; layer < WORLD_LAYERS; layer++){
        for (int i = 0; i < ROOM_WIDTH; i++){
            for (int j = 0; j < ROOM_HEIGHT; j++){
                f >> a.tiles[layer][i][j];
            }
        }
    }
    f >> a.connections[0];
    f >> a.connections[1];
    f >> a.connections[2];
    f >> a.connections[3];
    f.close();
    return a;
}