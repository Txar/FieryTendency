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
#include "game/Content/BulletTypes.hpp"
#include <algorithm>

int main()
{
    Room a;
    for (int layer = 0; layer < WORLD_LAYERS; layer++){
        for (int i = 0; i < ROOM_WIDTH; i++){
            for (int j = 0; j < ROOM_HEIGHT; j++){
                a.tiles[layer][i][j] = 3;
                if (layer == 0){
                    a.tiles[layer][i][j] = 2;
                }
                if (j == 0 && layer >= 2){
                    if (rand() % 5 == 4){
                        a.tiles[layer][i][j] = 7;
                    }
                    else {
                        a.tiles[layer][i][j] = 0;
                    }
                }
                /*if (i == 0){
                    a.tiles[layer][i][j] = 1;
                }*/
                if (i == 0 && j == 0){
                    a.tiles[layer][i][j] = 0;
                }
                if (layer == 2 && j == 3){
                    a.tiles[layer][i][j] = 5;
                }
                if (layer == 0 && j > 1 && j < 5 && i == 3){
                    a.tiles[layer][i][j] = 6;
                }
                if (j > 3 && j < 8 && i == 7){
                    a.tiles[layer][i][j] = 1;
                }
                if (i == 7 && j == 8){
                    a.tiles[layer][i][j] = 0;
                }
                if (i == 5 && j == 6){
                    a.tiles[layer][i][j] = 0;
                }
            };
        };
    }

    Room c;
    for (int layer = 0; layer < WORLD_LAYERS; layer++){
        for (int i = 0; i < ROOM_WIDTH; i++){
            for (int j = 0; j < ROOM_HEIGHT; j++){
                c.tiles[layer][i][j] = 3;
                if (layer == 0){
                    c.tiles[layer][i][j] = 2;
                }
                if (j == 0){
                    c.tiles[layer][i][j] = 0;
                }
                /*if (i == 0){
                    c.tiles[layer][i][j] = 1;
                }*/
            };
        };
    }

    a.connections[0] = true;
    a.connections[1] = true;
    a.connections[2] = false;
    a.connections[3] = false;

    std::cout << "a" << std::endl;
    
    data::ExportRoomTo(a, "room1.room");

    //Room b = LoadRoomFrom("room1.room");

    std::cout << "c" << std::endl;

    sf::Clock clock;
    printf("j\n");
    LoadStandardItems();
    LoadDefaultPallete();
    LoadStandardEntities();
    LoadBullets();

    sf::Vector2i resolution;
    resolution.x = 1280;
    resolution.y = 720;
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Voluntary Boundary");

    window.setFramerateLimit(60);

    float movement[2];
    int camera[4] = {0, 0, 0, 0};
    int cameraSpeed = TILE_SIZE * 4;
    bool previousMousePressed = false;
    bool currentMousePressed = false;

    sf::Vector2u windowSize;
    windowSize.x = window.getSize().x;
    windowSize.y = window.getSize().y;

    sf::View view;
    sf::Sprite visibleTiles;
    World world;
    world.SetPallete(defaultPallete);
    world.TileMapRoomFillTest();
    world.AddRoom(a);
    world.AddRoom(a);
    world.DrawWorld({(float)camera[0], (float)camera[1], (float)resolution.x, (float)resolution.y});
    
    entityTypes[0].x = TILE_SIZE * 2;
    entityTypes[0].y = TILE_SIZE * 3;
    printf("%f\n%f\n", entityTypes[0].x, entityTypes[0].y);
    world.SummonObject(entityTypes[0]);

    int fps = 0;

    std::cout << world.GetTileIndexFromCoordinates(128, 128, 0) << std::endl;

    visibleTiles.setScale(SCALING, SCALING);

    while (window.isOpen())
    {
        delta_time = clock.getElapsedTime().asSeconds();
        clock.restart();
        secondTimer += delta_time;

        if (secondTimer >= 1){
            secondTimer = 0;
            std::cout << fps << " fps" << std::endl;
            fps = 0;

            if (FPressed){
                Entity tempObject = entityTypes.at(0);
                tempObject.x = world.entityMap.at(0).x;
                tempObject.y = world.entityMap.at(0).y;
                tempObject.team = 1;
                world.SummonObject(tempObject);
            }
        }
        fps++;


        currentMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (!previousMousePressed && currentMousePressed){
            mouse = sf::Mouse::getPosition(window);
            sf::Vector2f bulletVelocity = shootBullet(mouse, {world.entityMap.at(0).x, world.entityMap.at(0).y}, {camera[0], camera[1]}, resolution, bulletTypes.at(0));
            world.SummonBullet(world.entityMap.at(0).x + TILE_SIZE * 0.75, world.entityMap.at(0).y + TILE_SIZE * 0.75, bulletVelocity, bulletTypes.at(0));
            std::cout << abs(bulletVelocity.x) + abs(bulletVelocity.y) << std::endl;
        }

        previousMousePressed = currentMousePressed;

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

        world.entityMap.at(0).Accelerate(movement[0] * cameraSpeed * delta_time, movement[1] * cameraSpeed * delta_time);

        camera[0] = world.entityMap.at(0).x - (windowSize.x / 2 / SCALING) + (TILE_SIZE * 1.5);
        camera[1] = world.entityMap.at(0).y - (windowSize.y / 2 / SCALING) + (TILE_SIZE * 1.5);

        /*if (abs(world.entityMap.at(0).x - camera[0] - (windowSize.x / 2 / SCALING)) > 10)
            camera[2] += (world.entityMap.at(0).x - camera[0] - (windowSize.x / 2 / SCALING)) / abs(world.entityMap.at(0).x - camera[0] - (windowSize.x / 2 / SCALING)) * cameraSpeed / 10;

        if (abs(world.entityMap.at(0).y - camera[1] - (windowSize.y / 2 / SCALING)) > 10)
            camera[3] += (world.entityMap.at(0).y - camera[1] - (windowSize.y / 2 / SCALING)) / abs(world.entityMap.at(0).y - camera[1] - (windowSize.y / 2 / SCALING)) * cameraSpeed / 10;
        */

        world.Update({(float)camera[0], (float)camera[1], (float)resolution.x / SCALING, (float)resolution.y / SCALING});
        
        //camera[0] += camera[2] * delta_time;
        //camera[1] = camera[3] * delta_time;

        view.reset({(float)camera[0], (float)camera[1], (float)windowSize.x, (float)windowSize.y});
        window.setView(view);

        visibleTiles.setTexture(world.visibleTiles);

        visibleTiles.setPosition({(float)camera[0], (float)camera[1]});
        window.clear();
        window.draw(visibleTiles);
        window.display();
    }

    return 0;
}