#include "game/World/TileSet.hpp"
#include <vector>
#include "game/Object/Entity.hpp"
#include "game/World/Room.hpp"
#include "SFML/Graphics.hpp"
#include "game/Content/WorldProperties.hpp"
#include "game/Content/StandardEntities.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game/Weapon/Bullet.hpp"
#include "game/Content/BulletTypes.hpp"
#pragma once

sf::Texture MISSING_TEXTURE;

const int layers = WORLD_LAYERS;

const int WORLD_BORDER = 64 * TILE_SIZE;

float secondTimer = 0;

class World {
    public:
        sf::Color skyColor = {220, 150, 120};
        sf::Color topSkyColor = {120, 160, 230};
        int width = WORLD_WIDTH;
        int height = WORLD_HEIGHT;
        int tileMap[WORLD_WIDTH / ROOM_WIDTH][WORLD_HEIGHT / ROOM_HEIGHT];

        std::vector<Room> rooms;
        std::vector<Entity> entityMap = {};
        std::vector<Entity> bulletMap = {};

        TileSet pallete;
        sf::Texture visibleTiles;
        sf::RenderTexture entityTexture;
        sf::RenderTexture healthBarsTexture;

        World() {
            MISSING_TEXTURE.loadFromFile("assets/notexture.png");
        }

        void AddRoom(Room room){
            rooms.push_back(room);
        };
 
        int GetTileIndexFromCoordinates(double x, double y, int layer){
            return rooms.at(tileMap[(int)ceil(x / ROOM_WIDTH / TILE_SIZE)][(int)ceil(y / ROOM_HEIGHT / TILE_SIZE)])
            .tiles[layer][SnapToTileGrid(x)/TILE_SIZE % ROOM_WIDTH]
            [SnapToTileGrid(y)/TILE_SIZE % ROOM_HEIGHT];
        };

        void UpdateEntities(sf::FloatRect viewArea){
            Entity tempEntity;
            for (int i = 0; i < (int)entityMap.size(); i++){
                tempEntity = entityMap.at(i);

                if (tempEntity.dead){
                    if (tempEntity.justDied){
                        DropLoot(i);
                        tempEntity.justDied = false;
                        entityMap.at(i) = tempEntity;
                    }
                    continue;
                }
                for (int b = 0; b < (int)tempEntity.collisionBoxes.size(); b++){

                    for (int bullet = 0; bullet < (int)bulletMap.size(); bullet++){

                        if (tempEntity.collisionBoxes.at(b).CheckIfCollidesWith(bulletMap.at(bullet).collisionBoxes.at(0)) && 
                        !bulletMap.at(bullet).dead && (bulletMap.at(bullet).team != tempEntity.team)
                        && tempEntity.invincibilityTimer <= 0){

                            tempEntity.collisionBoxes.at(b).damageTaken = bulletMap.at(bullet).collisionDamage;
                            bulletMap.at(bullet).piercing--;

                            if (bulletMap.at(bullet).piercing < 0){
                                bulletMap.at(bullet).Die();
                            }
                        }
                    }
                }

                tempEntity.Update();
                if (tempEntity.dead){
                    entityMap.at(i) = tempEntity;
                    continue;
                }
                
                tempEntity.x += tempEntity.velocity.x;
                if (CheckIfEntityCollides(tempEntity)){
                    tempEntity.x -= tempEntity.velocity.x;
                    tempEntity.velocity.x = 0;
                }

                tempEntity.y += tempEntity.velocity.y;
                if (CheckIfEntityCollides(tempEntity)){
                    tempEntity.y -= tempEntity.velocity.y;
                    tempEntity.velocity.y = 0;
                }
                
                if (!tempEntity.floating){
                    tempEntity = ApplyFriction(tempEntity);
                }

                entityMap.at(i) = tempEntity;
            }
            
            for (int i = 0; i < (int)bulletMap.size(); i++){
                
                bulletMap.at(i).UpdateTrail();

                tempEntity = bulletMap.at(i);

                if (tempEntity.dead){
                    continue;
                }

                tempEntity.Update();
                if (tempEntity.dead){
                    bulletMap.at(i) = tempEntity;
                    continue;
                }
                
                tempEntity.x += tempEntity.velocity.x;
                if (CheckIfEntityCollides(tempEntity)){
                    if (tempEntity.bounces > 0){
                        tempEntity.x -= tempEntity.velocity.x;
                        tempEntity.velocity.x = -tempEntity.velocity.x;
                        tempEntity.bounces--;
                    }
                    else {
                        tempEntity.Die();
                    }
                }

                tempEntity.y += tempEntity.velocity.y;
                if (CheckIfEntityCollides(tempEntity)){
                    if (tempEntity.bounces > 0){
                        tempEntity.y -= tempEntity.velocity.y;
                        tempEntity.velocity.y = -tempEntity.velocity.y;
                        tempEntity.bounces--;
                    }
                    else {
                        tempEntity.Die();
                    }
                }
                    
                TrailPoint tempTrail;
                tempTrail.x = tempEntity.x;
                tempTrail.y = tempEntity.y;
                tempTrail.timer = 0.1;
                tempEntity.trailPoints.push_back(tempTrail);
            

                bulletMap.at(i) = tempEntity;
            }
        };

        void Update(sf::FloatRect viewArea){
            //DrawBullets(viewArea);
            DrawEntities(viewArea);
            DrawHealthBars(viewArea);
            entityTexture.display();
            healthBarsTexture.display();
            
            DrawWorld(viewArea);
            UpdateEntities(viewArea);
        };

        void SetPallete(TileSet tiles){
            pallete = tiles;
        };

        bool CheckIfEntityCollides(Entity entity){
            for (CollisionBox i : entity.collisionBoxes){
                for (int j = 0; j < i.width; j += floor(TILE_SIZE / 16)){
                    for (int k = 0; k < i.height; k += floor(TILE_SIZE / 16)){
                        if (pallete.IsSolid(GetTileIndexFromCoordinates(entity.x + i.offset.x + entity.velocity.x + j, entity.y + i.offset.y + k, 1))){
                            return true;
                        }
                    }
                }
            }
            return false;
        };

        Entity ApplyFriction(Entity entity){
            entity.velocity.x -= entity.velocity.x * pallete.GetFriction(GetTileIndexFromCoordinates(entity.x, entity.y, 0));
            entity.velocity.y -= entity.velocity.y * pallete.GetFriction(GetTileIndexFromCoordinates(entity.x, entity.y, 0));
            return entity;
        }

        int SummonObject(Entity object){
            int index = entityMap.size();
            entityMap.push_back(object);
            return index;
        };

        void SummonBullet(float x, float y, sf::Vector2f v, Bullet b){
            Entity bullet;
            bullet.bullet = true;
            bullet.bounces = b.bounces;
            bullet.floating = true;
            bullet.collisionDamage = b.damage;
            bullet.piercing = b.piercing;
            bullet.team = b.team;

            sf::Sprite bulletSprite;
            bulletSprite.setTexture(bulletTexture);
            bulletSprite.setTextureRect(b.sprite);
            bullet.AddSprite(bulletSprite);

            b.sprite.top += b.sprite.height;
            bulletSprite.setTextureRect(b.sprite);
            bullet.trailSprite = bulletSprite;

            bullet.velocity = v;
            bullet.x = x;
            bullet.y = y;

            CollisionBox box;
            box.width = b.width;
            box.height = b.height;
            bullet.collisionBoxes.push_back(box);

            bulletMap.push_back(bullet);
        }

        bool IsASolid(int x, int y, int layer){
            return pallete.IsSolid(GetTileIndexFromCoordinates(x * TILE_SIZE, y * TILE_SIZE, layer));
        };

        void DropLoot(int entityIndex){
            std::cout << "a\n";
            std::vector<ItemDrop> loot = entityMap.at(entityIndex).loot;
            for (int i = 0; i < (int)loot.size(); i++){
                DropItem(loot.at(i), entityMap.at(entityIndex).x, entityMap.at(entityIndex).y);
            }
        }

        void DropItem(ItemDrop a, int x, int y){
            Entity tempEntity = standard_item_entity;
            tempEntity.x = x;
            tempEntity.y = y;
            tempEntity.AddSprite(a.item.sprite);

            SummonObject(tempEntity);
        }

        void DrawWorld(sf::FloatRect area){
            sf::IntRect renderArea = {SnapToTileGrid(area.left), SnapToTileGrid(area.top), SnapToTileGrid(area.width), SnapToTileGrid(area.height)};
            sf::RenderTexture texture;
            
            if (!texture.create(area.width, area.height) || !visibleTiles.create(area.width, area.height)){
                printf("Failed to create tileMap texture\n");
            };

            sf::RectangleShape topSkyTile({TILE_SIZE, TILE_SIZE});
            topSkyTile.setFillColor(topSkyColor);

            texture.clear(skyColor);

            int g = 0;
        
            for (int layer = 0; layer < layers; layer++){
                for (int i = renderArea.left/TILE_SIZE - 1; i < (renderArea.left + renderArea.width + TILE_SIZE) / TILE_SIZE; i++){
                    for (int j = renderArea.top/TILE_SIZE - 1; j < (renderArea.top + renderArea.height + TILE_SIZE) / TILE_SIZE; j++){

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
                    sf::Sprite entities(entityTexture.getTexture());
                    texture.draw(entities);
                }
            }
            sf::Sprite t(healthBarsTexture.getTexture());
            texture.draw(t);
            texture.display();
            visibleTiles = texture.getTexture();
        };

        void DrawEntities(sf::FloatRect area){
            sf::Sprite currentSprite;
            entityTexture.create(area.width, area.height);
            entityTexture.clear({0, 0, 0, 0});

            sf::FloatRect tempArea = area;
            tempArea.left -= TILE_SIZE * 2;
            tempArea.top -= TILE_SIZE * 2;
            tempArea.width += TILE_SIZE * 2;
            tempArea.height += TILE_SIZE * 2;

            for (Entity i : entityMap){
                if (i.dead && tempArea.contains(i.x, i.y) && (int(i.invincibilityTimer * 10) % 2 || i.invincibilityTimer <= 0)){
                    for (ObjectSprite j : i.dead_sprites){
                            currentSprite = j.sprite;
                            currentSprite.setPosition({i.x + j.offset.x + TILE_SIZE - area.left, i.y + j.offset.y + TILE_SIZE - area.top});
                            entityTexture.draw(currentSprite);
                    }
                }
            }

            for (Entity i : entityMap){
                if (!i.dead && tempArea.contains(i.x, i.y) && (int(i.invincibilityTimer * 10) % 2 || i.invincibilityTimer <= 0)){
                    for (ObjectSprite j : i.sprites){
                        currentSprite = j.sprite;
                        currentSprite.setPosition({i.x + j.offset.x + TILE_SIZE - area.left, i.y + j.offset.y + TILE_SIZE - area.top});
                        entityTexture.draw(currentSprite);
                    }
                }
            }

            for (Entity i : bulletMap){
                for (TrailPoint k : i.trailPoints){
                    if (i.x == k.x && i.y == k.y){
                        continue;
                    }
                    currentSprite = i.trailSprite;
                    currentSprite.setPosition(k.x + TILE_SIZE - area.left, k.y + TILE_SIZE - area.top);
                    entityTexture.draw(currentSprite);
                }
            }

            for (Entity i : bulletMap){
                if (tempArea.contains(i.x, i.y)){
                    for (ObjectSprite j : i.sprites){
                        if (i.dead){
                            break;
                        }
                        currentSprite = j.sprite;
                        currentSprite.setPosition({i.x + j.offset.x + TILE_SIZE - area.left, i.y + j.offset.y + TILE_SIZE - area.top});
                        entityTexture.draw(currentSprite);
                    }
                }
            }            
        }

        void DrawBullets(sf::FloatRect area){
            sf::Sprite currentSprite;
            for (Entity i : bulletMap){
                if (area.contains(i.x, i.y)){
                    currentSprite = i.sprites.at(0).sprite;
                    currentSprite.setPosition(i.x + i.sprites.at(0).offset.x + TILE_SIZE - area.left, i.y + i.sprites.at(0).offset.y + TILE_SIZE - area.top);
                    entityTexture.draw(currentSprite);
                }
            }
        }

        void DrawHealthBars(sf::FloatRect area){
            sf::Sprite currentSprite;
            healthBarsTexture.create(area.width, area.height);
            healthBarsTexture.clear({0, 0, 0, 0});
            for (Entity i : entityMap){
                if (area.contains(i.x, i.y) && !i.dead){
                    currentSprite = i.HPsprite.sprite;
                    currentSprite.setPosition(i.x + i.HPsprite.offset.x + TILE_SIZE - area.left, i.y + i.HPsprite.offset.y + TILE_SIZE - area.top);
                    healthBarsTexture.draw(currentSprite);   
                }
            }
        }

        void TileMapRoomFillTest(){
            srand(time(NULL));
            for (int i = 0; i < WORLD_WIDTH/ROOM_WIDTH; i++){
                for (int j = 0; j < WORLD_HEIGHT/ROOM_HEIGHT; j++){
                    tileMap[i][j] = rand() % 2;
                }
            }
            tileMap[1][1] = 0;
        };
};