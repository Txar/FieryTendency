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

    defaultPallete.LoadTexture("assets/tiles.png");
    defaultPallete.GenerateSprites(3, 1);
};