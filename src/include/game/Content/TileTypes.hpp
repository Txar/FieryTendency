#include "game/World/Tile.hpp"
#include "game/World/TileSet.hpp"

TileSet defaultPallete;

void LoadDefaultPallete(){
    Tile wallEdge;
    wallEdge.solid = true;
    wallEdge.sprite = 0;
    defaultPallete.AddTile(wallEdge);
    delete[] &wallEdge;

    Tile wall;
    wall.solid = true;
    wall.sprite = 1;
    defaultPallete.AddTile(wall);
    delete[] &wall;

    Tile floor;
    floor.solid = false;
    floor.sprite = 2;
    defaultPallete.AddTile(floor);
    delete[] &floor;

    Tile air;
    air.solid = false;
    air.sprite = 3;
    defaultPallete.AddTile(air);
    delete[] &air;

    defaultPallete.LoadTexture("assets/tiles.png");
    defaultPallete.GenerateSprites(4, 2);
};