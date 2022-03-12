#include "SFML/Graphics.hpp"
#include "game/Object/CollisionBox.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "game/Data/RoomLoadExport.hpp"
#include "game/Input.hpp"
#include "game/World/World.hpp"
#include "game/Content/TileTypes.hpp"
#include "game/Content/WorldProperties.hpp"

int main()
{
    Room a;
    for (int layer = 0; layer < WORLD_LAYERS; layer++){
        for (int i = 0; i < ROOM_WIDTH; i++){
            for (int j = 0; j < ROOM_HEIGHT; j++){
                a.tiles[layer][i][j] = 3;
                if (j == 0){
                    a.tiles[layer][i][j] = 0;
                }
                if (i == 0){
                    a.tiles[layer][i][j] = 1;
                }
                if (layer == 0 && i > 0 && j > 0){
                    a.tiles[layer][i][j] = 2;
                }
                if (layer == 2 && i > 0 && j == 3){
                    a.tiles[layer][i][j] = 5;
                }
                if (layer == 0 && j > 1 && j < 5 && i == 3){
                    a.tiles[layer][i][j] = 6;
                }
            };
        };
    }

    Room c;
    for (int layer = 0; layer < WORLD_LAYERS; layer++){
        for (int i = 0; i < ROOM_WIDTH; i++){
            for (int j = 0; j < ROOM_HEIGHT; j++){
                c.tiles[layer][i][j] = 3;
                if (j == 0){
                    c.tiles[layer][i][j] = 0;
                }
                if (i == 0){
                    c.tiles[layer][i][j] = 1;
                }
            };
        };
    }

    a.connections[0] = true;
    a.connections[1] = true;
    a.connections[2] = false;
    a.connections[3] = false;

    std::cout << "a" << std::endl;
    
    ExportRoomTo(a, "room1.room");

    Room b = LoadRoomFrom("room1.room");

    std::cout << "c" << std::endl;
    //std::cout << b.tiles[0][0] << " " << b.connections[1] << " " << b.tiles[5][5];



    sf::Clock clock;

    LoadDefaultPallete();

    sf::Vector2i resolution;
    resolution.x = 1280;
    resolution.y = 720;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Voluntary Boundary");

    //window.setFramerateLimit(60);

    int movement[2];
    int camera[4] = {0, 0, 0, 0};
    float cameraVelocity[2] = {0, 0};
    float cameraSpeed = 16;

    sf::Vector2u windowSize;
    windowSize.x = window.getSize().x;
    windowSize.y = window.getSize().y;

    sf::View view;
    sf::Sprite visibleTiles;
    World world;
    std::cout << a.tiles[0][0][0] << std::endl;
    world.SetPallete(defaultPallete);
    world.TileMapRoomFillTest();
    world.AddRoom(b);
    world.AddRoom(c);
    world.DrawWorld({(float)camera[0], (float)camera[1], 1920, 1080});

    while (window.isOpen())
    {
        delta_time = clock.getElapsedTime().asSeconds();
        clock.restart();
        std::cout << 1 / delta_time << " fps" << std::endl;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::Resized){
                windowSize.x = window.getSize().x;
                windowSize.y = window.getSize().y;
            }
        }

        movement[0] = 0;
        movement[1] = 0;
        MoveKeyInput(movement);

        cameraVelocity[0] += movement[0] * cameraSpeed;
        cameraVelocity[1] += movement[1] * cameraSpeed;

        //all camera stuff is temporary, just for testing
        if (camera[0] + cameraVelocity[0] < 0 - WORLD_BORDER){
            cameraVelocity[0] = 0;
        }
        if (camera[0] + cameraVelocity[0] > world.width * TILE_SIZE + WORLD_BORDER){
            cameraVelocity[0] = 0;
        }
        if (camera[1] + cameraVelocity[1] < 0 - WORLD_BORDER){
            cameraVelocity[1] = 0;
        }
        if (camera[1] + cameraVelocity[1] > world.height * TILE_SIZE + WORLD_BORDER){
            cameraVelocity[1] = 0;
        }


        camera[0] += cameraVelocity[0] * delta_time;
        camera[1] += cameraVelocity[1] * delta_time;

        cameraVelocity[0] -= cameraVelocity[0] * 1.2 * delta_time;
        cameraVelocity[1] -= cameraVelocity[1] * 1.2 * delta_time;

        world.DrawWorld({(float)camera[0], (float)camera[1], 1920, 1080});
        if (camera[2] != camera[0] || camera[3] != camera[1]){
            camera[2] = camera[0];
            camera[3] = camera[1];
        }

        view.reset({(float)camera[0], (float)camera[1], (float)windowSize.x, (float)windowSize.y});
        window.setView(view);

        visibleTiles.setTexture(world.visibleTiles);

        visibleTiles.setPosition({(float)camera[0], (float)camera[1]});
        window.clear();
        window.draw(visibleTiles);
        //window.draw(world.pallete.GetSprite(0));
        window.display();
    }

    return 0;
}