#include "game/World/TileSet.hpp"
#include <vector>
#include "game/Object/Entity.hpp"
#include "game/World/Room.hpp"
#include "SFML/Graphics.hpp"

const int layers = 3;

const int WORLD_BORDER = 64 * TILE_SIZE;

class World {
    public:
        sf::Color skyColor = {220, 150, 120};
        int width = 100;
        int height = 100;
        int tileMap[layers][100][100];
        std::vector<Room> rooms = {};
        std::vector<Entity> objectMap = {};
        TileSet pallete;
        sf::Texture visibleTiles;
        
        void InitializeTileMap(int w, int h, TileSet tiles){
            pallete = tiles;
            width = w, height = h;

            //int tileMap[width][height];
        };

        int SummonObject(Entity object){
            int index = objectMap.size();
            objectMap.push_back(object);
            return index;
        };

        bool IsASolid(int x, int y, int layer){
            return (pallete.IsSolid(tileMap[layer][x][y]));
        };

        void DrawWorld(sf::FloatRect area){
            sf::IntRect renderArea = {SnapToTileGrid(area.left), SnapToTileGrid(area.top), SnapToTileGrid(area.width), SnapToTileGrid(area.height)};
            sf::RenderTexture texture;
            
            if (!texture.create(area.width, area.height) || !visibleTiles.create(area.width, area.height)){
                printf("Failed to create tileMap texture\n");
            };

            sf::RectangleShape backgroundTile({area.width, TILE_SIZE});

            texture.clear(skyColor);

            /*for (int a = renderArea.top/TILE_SIZE - TILE_SIZE; a < (renderArea.top + renderArea.height + TILE_SIZE * 5); a++){

                backgroundTile.setFillColor({ (sf::Uint8)(255 * a / (height + (WORLD_BORDER / TILE_SIZE * 2))),
                    (sf::Uint8)(255 * a / (height + (WORLD_BORDER / TILE_SIZE * 2))),
                    (sf::Uint8)(255 * a / (WORLD_BORDER / TILE_SIZE * 2))});
                
                backgroundTile.setPosition({0, a*TILE_SIZE - area.top});

                texture.draw(backgroundTile);
            }*/

            for (int layer = 0; layer < layers; layer++){
                for (int i = renderArea.left/TILE_SIZE - TILE_SIZE; i < (renderArea.left + renderArea.width + TILE_SIZE * 5)/TILE_SIZE; i++){
                    for (int j = renderArea.top/TILE_SIZE - TILE_SIZE; j < (renderArea.top + renderArea.height + TILE_SIZE * 5)/TILE_SIZE; j++){

                        if (!(i >= width || j >= height || i < 0 || j < 0) && tileMap[layer][i][j] != 3){ //draws the tiles

                            pallete.sprites[pallete.GetSpriteIndex(tileMap[layer][i][j])].setPosition(
                                {(float)i*TILE_SIZE - area.left, j*TILE_SIZE - area.top - (float)(TILE_SIZE/1.8)*layer});
                            
                            texture.draw(pallete.GetSprite(tileMap[layer][i][j]));
                            
                            bool ShadeDone = false;

                            if (layers > 1 && tileMap[layer][i][j] != 3){
                                for (int a = layer + 1; a < layers && !ShadeDone; a++){
                                    if (a == layer + 1 && pallete.IsSolid(tileMap[layer][i][j])){
                                        ShadeDone = true;
                                    }
                                    else if (pallete.IsSolid(tileMap[a][i][j])){
                                        pallete.sprites[pallete.GetShadowIndex(tileMap[a][i][j])].setPosition(
                                        {i*TILE_SIZE - area.left,
                                         j*TILE_SIZE - area.top});

                                        texture.draw(pallete.GetShadow(tileMap[a][i][j]));
                                        ShadeDone = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            texture.display();
            visibleTiles = texture.getTexture();
        };

        void FillTileMapWith(int num){
            for (int layer = 0; layer < layers; layer++){
                for (int i = 0; i < width; i++){
                    for (int j = 0; j < height; j++){
                        tileMap[layer][i][j] = num;
                    }
                }
            }
        };

        void TileMapRoomFillTest(){
            for (int layer = 0; layer < layers; layer++){
                for (int i = 0; i < width; i++){
                    for (int j = 0; j < height; j++){
                        if ((i == 0 || i == width - 1) && j != height - 1){
                            tileMap[layer][i][j] = 1;
                        }
                        else if ((i > 0 && i < width - 1) && (j > 0 && j < height - 1)){
                            if (layer == 0){
                                tileMap[layer][i][j] = 2;
                            }
                            else {
                                tileMap[layer][i][j] = 3;
                            }
                        }
                        else if (j == 0 || j == height - 1){
                            tileMap[layer][i][j] = 0;
                        }
                        if (layer == 3 && j == 7){
                            tileMap[layer][i][j] = 0;
                        }
                        if (layer == 3 && i == 9 && j < 12){
                            tileMap[layer][i][j] = 1;
                        }
                        if (layer == 3 && i == 9 && j == 12){
                            tileMap[layer][i][j] = 0;
                        }
                    }
                }
            }
        };
};