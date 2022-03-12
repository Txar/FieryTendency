#include "game/World/Tile.hpp"
#include "game/World/TileSet.hpp"

TileSet defaultPallete;

//enum tiles;

void LoadDefaultPallete(){
    Tile wallEdge;
    wallEdge.solid = true;
    wallEdge.sprite = 0;
    defaultPallete.AddTile(wallEdge);

    Tile wall;
    wall.solid = true;
    wall.sprite = 1;
    defaultPallete.AddTile(wall);

    Tile floor;
    floor.solid = false;
    floor.sprite = 2;
    floor.floor = true;
    defaultPallete.AddTile(floor);

    Tile air;
    air.solid = false;
    air.sprite = 3;
    defaultPallete.AddTile(air);

    Tile ceiling;
    ceiling.solid = true;
    ceiling.sprite = 4;
    defaultPallete.AddTile(ceiling);

    Tile ceilingEdge;
    ceilingEdge.solid = true;
    ceilingEdge.sprite = 5;
    defaultPallete.AddTile(ceilingEdge);

    Tile metalFloor;
    metalFloor.solid = false;
    metalFloor.reflecting = true;
    metalFloor.sprite = 6;
    metalFloor.floor = true;
    defaultPallete.AddTile(metalFloor);

    //enum tiles {wallEdge, wall, floor, air, ceiling, ceilingEdge};

    delete[] &metalFloor;
    delete[] &ceilingEdge;
    delete[] &ceiling;
    delete[] &air;
    delete[] &floor;
    delete[] &wall;
    delete[] &wallEdge;
    delete[] &metalFloor;

    defaultPallete.LoadTexture("assets/tiles.png");
    defaultPallete.GenerateSprites(7, 3);
};