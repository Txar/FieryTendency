#include "game/World/TileSet.hpp"
#include <vector>
#include "game/Object/Entity.hpp"
#include "game/World/Room.hpp"
#include "SFML/Graphics.hpp"
#include "game/Content/WorldProperties.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#pragma once

const int layers = WORLD_LAYERS;

const int WORLD_BORDER = 64 * TILE_SIZE;

class World {
    public:
        sf::Color skyColor = {220, 150, 120};
        sf::Color topSkyColor = {120, 160, 230};
        int width = WORLD_WIDTH;
        int height = WORLD_HEIGHT;
        int tileMap[WORLD_WIDTH / ROOM_WIDTH][WORLD_HEIGHT / ROOM_HEIGHT];
        std::vector<Room> rooms;
        std::vector<Entity> entityMap = {};
        TileSet pallete;
        sf::Texture visibleTiles;
        sf::Texture entitiyTexture;

        void AddRoom(Room room){
            rooms.push_back(room);
        };
 
        int GetTileIndexFromCoordinates(int x, int y, int layer){
            return rooms.at(tileMap[(int)ceil(x / ROOM_WIDTH / TILE_SIZE)][(int)ceil(y / ROOM_HEIGHT / TILE_SIZE)])
            .tiles[layer][SnapToTileGrid(x)/TILE_SIZE % ROOM_WIDTH]
            [SnapToTileGrid(y)/TILE_SIZE % ROOM_HEIGHT];
        };

        void UpdateEntities(sf::FloatRect viewArea){
            
        };

        void Update(sf::FloatRect viewArea){
            DrawWorld(viewArea);
        };

        void SetPallete(TileSet tiles){
            pallete = tiles;
        };

        bool CheckIfEntityCollides(Entity entity){
            for (CollisionBox i : entity.collisionBoxes){
                for (int j = 0; j < i.width; j += TILE_SIZE){
                    for (int k = 0; k < i.height; k += TILE_SIZE){    
                        if (pallete.IsSolid(GetTileIndexFromCoordinates(i.x + i.offset.x + entity.velocity.x, i.y + i.offset.y, 0)) ||
                        pallete.IsSolid(GetTileIndexFromCoordinates(i.x + i.offset.x, i.y + i.offset.y + entity.velocity.y, 0))){
                        }
                    }
                }
            }
            return false;
        };

        /*bool CheckCollisionsWithTileMap(CollisionBox box){
            bool collides = false;
            for (int i = SnapToTileGrid(box.x); i < SnapToTileGrid(box.x + box.width + TILE_SIZE); i += TILE_SIZE){
                for (int j = SnapToTileGrid(box.y); i < SnapToTileGrid(box.y + box.height + TILE_SIZE); j += TILE_SIZE){
                    if (pallete.IsSolid(tileMap[0][i/TILE_SIZE][j/TILE_SIZE])){
                        collides = true;
                    }
                }
            }
            return collides;
        };*/

        int SummonObject(Entity object){
            int index = entityMap.size();
            entityMap.push_back(object);
            return index;
        };

        bool IsASolid(int x, int y, int layer){
            return pallete.IsSolid(GetTileIndexFromCoordinates(x * TILE_SIZE, y * TILE_SIZE, layer));
        };

        void DrawWorld(sf::FloatRect area){
            sf::IntRect renderArea = {SnapToTileGrid(area.left), SnapToTileGrid(area.top), SnapToTileGrid(area.width), SnapToTileGrid(area.height)};
            sf::RenderTexture texture;
            
            std::cout << "b" << std::endl;
            if (!texture.create(area.width, area.height) || !visibleTiles.create(area.width, area.height)){
                printf("Failed to create tileMap texture\n");
            };

            sf::RectangleShape topSkyTile({TILE_SIZE, TILE_SIZE});
            topSkyTile.setFillColor(topSkyColor);

            texture.clear(skyColor);

            int g = 0;
        
            for (int layer = 0; layer < layers; layer++){
                for (int i = renderArea.left/TILE_SIZE - 1; i < (renderArea.left + renderArea.width + TILE_SIZE)/TILE_SIZE; i++){
                    for (int j = renderArea.top/TILE_SIZE - 1; j < (renderArea.top + renderArea.height + TILE_SIZE)/TILE_SIZE; j++){

                        if (!(i >= width || j >= height || i < 0 || j < 0) && GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer) != 3){ //draws the tiles
                            g++;

                            if (layers > 1 && pallete.IsReflecting(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer))){
                                topSkyTile.setPosition({
                                 i*TILE_SIZE - area.left,
                                 j*TILE_SIZE - area.top});
                                         
                                texture.draw(topSkyTile);
                                for (int a = layer + 1; a < layers; a++){
                                    if (pallete.IsSolid(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, a))){
                                        pallete.sprites[pallete.GetBottomIndex(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, a))].setPosition(
                                        {i*TILE_SIZE - area.left,
                                         j*TILE_SIZE - area.top});

                                        texture.draw(pallete.GetBottom(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, a)));
                                    }
                                }
                                
                            }

                            pallete.sprites[pallete.GetSpriteIndex(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer))].setPosition(
                                {(float)i*TILE_SIZE - area.left, j*TILE_SIZE - area.top - (float)(TILE_SIZE/1.8)*layer});
                            
                            texture.draw(pallete.GetSprite(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer)));
                            
                            bool ShadeDone = false;

                            if (layers > 1 && GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer) != 3 && !pallete.IsReflecting(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer))){
                                for (int a = layer + 1; a < layers && !ShadeDone; a++){
                                    if (a == layer + 1 && pallete.IsSolid(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer))){
                                        ShadeDone = true;
                                    }
                                    else if (pallete.IsSolid(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, a))){
                                        pallete.sprites[pallete.GetShadowIndex(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, a))].setPosition(
                                        {i*TILE_SIZE - area.left,
                                         j*TILE_SIZE - area.top});

                                        texture.draw(pallete.GetShadow(GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, a)));
                                        ShadeDone = true;
                                    }
                                }
                            }
                        }
                    }
                }

                if (layer == 0){
                    sf::Sprite entities(entitiyTexture);
                    texture.draw(entities);
                }
            }
            std::cout << g << std::endl;
            texture.display();
            visibleTiles = texture.getTexture();
        };

        /*void FillTileMapWith(int num){
            for (int layer = 0; layer < layers; layer++){
                for (int i = 0; i < width; i++){
                    for (int j = 0; j < height; j++){
                        GetTileIndexFromCoordinates(i * TILE_SIZE, j  * TILE_SIZE, layer) = num;
                    }
                }
            }
        };*/

        void TileMapRoomFillTest(){
            srand(time(NULL));
            for (int i = 0; i < WORLD_WIDTH/ROOM_WIDTH; i++){
                for (int j = 0; j < WORLD_HEIGHT/ROOM_HEIGHT; j++){
                    tileMap[i][j] = rand() % 2;
                }
            }
        };
};