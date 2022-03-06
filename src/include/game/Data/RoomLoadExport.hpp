#include "game/World/Room.hpp"
#include <fstream>
#include <iostream>

void ExportRoomTo(Room room, std::string path){
    std::ofstream f;
    f.open(path);
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 12; j++){
            f << room.tiles[i][j] << std::endl;
            std::cout << room.tiles[i][j] << std::endl;
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
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 12; j++){
            f >> a.tiles[i][j];
        }
    }
    f >> a.connections[0];
    f >> a.connections[1];
    f >> a.connections[2];
    f >> a.connections[3];
    f.close();
    return a;
}