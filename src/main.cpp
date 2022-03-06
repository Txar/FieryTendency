#include "SFML/Graphics.hpp"
#include "game/Object/CollisionBox.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "game/Data/RoomLoadExport.hpp"
#include "game/Input.hpp"
#include "game/World/World.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Voluntary Boundary");

    window.setFramerateLimit(60);

    TileSet pallete;

    pallete.LoadTexture("assets/wall.png");
    pallete.GenerateSprites(2, 1);

    int movement[2];
    float camera[2] = {0, 0};
    float cameraVelocity[2] = {0, 0};

    Tile tile1;
    tile1.sprite = 0;
    tile1.id = 0;
    tile1.solid = true;

    pallete.AddTile(tile1);

    sf::View view;
    sf::Sprite visibleTiles;

    World world;
    world.InitializeTileMap(100, 100, pallete);
    world.FillTileMapWith(0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        movement[0] = 0;
        movement[1] = 0;
        MoveKeyInput(movement);

        cameraVelocity[0] += movement[0];
        cameraVelocity[1] += movement[1];

        camera[0] += cameraVelocity[0];
        camera[1] += cameraVelocity[1];

        cameraVelocity[0] -= cameraVelocity[0] * 0.02;
        cameraVelocity[1] -= cameraVelocity[1] * 0.02;

        sf::Vector2u windowSize = window.getSize();

        view.reset(sf::FloatRect(camera[0], camera[1], windowSize.x, windowSize.y));
        window.setView(view);

        world.DrawWorld({camera[0], camera[1], windowSize.x, windowSize.y});

        visibleTiles.setTexture(world.texture.getTexture());

        visibleTiles.setPosition({camera[0], camera[1]});
        window.clear();
        window.draw(visibleTiles);
        //window.draw(world.pallete.GetSprite(0));
        window.display();
    }


    CollisionBox A, B;
    A.x = 32;
    A.y = 32;
    //std::cout << A.CheckIfCollidesWith(B);

    Room a;
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 12; j++){
            a.tiles[i][j] = j + i;
            //std::cout << j + i << std::endl;
        };
    };

    a.connections[0] = true;
    a.connections[1] = true;
    a.connections[2] = false;
    a.connections[3] = false;

    //std::cout << room1.is_open();
    
    ExportRoomTo(a, "room1.room");

    Room b = LoadRoomFrom("room1.room");
    
    std::cout << b.tiles[0][0] << " " << b.connections[1] << " " << b.tiles[5][5];

    return 0;
}