#include "game/World/TileSet.hpp"
#include <vector>
#include "game/Object/Entity.hpp"
#include "game/World/Room.hpp"
#include "SFML/Graphics.hpp"

class World {
    public:
        int width =100;
        int height = 100;
        int tileMap[100][100];
        std::vector<Room> rooms = {};
        std::vector<Entity> objectMap = {};
        TileSet pallete;
        sf::RenderTexture texture;
        
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

        bool IsASolid(int x, int y){
            return (pallete.IsSolid(tileMap[x][y]));
        };

        void DrawWorld(sf::FloatRect area){
            sf::IntRect renderArea = {SnapToTileGrid(area.left), SnapToTileGrid(area.top), SnapToTileGrid(area.width), SnapToTileGrid(area.height)};

            if (!texture.create(area.width, area.height)){
                printf("Failed to create tileMap texture\n");
            };
            std::cout << area.width << " " << area.height << std::endl;

            std::cout << texture.getView().getSize().x << " " << texture.getView().getSize().y << std::endl;
            sf::Sprite currentSprite;

            texture.clear(sf::Color::Red);

            for (int i = renderArea.left/TILE_SIZE - TILE_SIZE; i < (renderArea.left + renderArea.width)/TILE_SIZE; i++){
                for (int j = renderArea.top/TILE_SIZE - TILE_SIZE; j < (renderArea.top + renderArea.height)/TILE_SIZE; j++){

                    if (!(i >= width || j >= height || i < 0 || j < 0)){

                        currentSprite = pallete.GetSprite(tileMap[i][j]);

                        currentSprite.setPosition({(float)i*TILE_SIZE-area.left, (float)j*TILE_SIZE-area.top});
                        
                        texture.draw(currentSprite);
                    }
                }
            }
            texture.display();
        };

        void FillTileMapWith(int num){
            for (int i = 0; i < width; i++){
                for (int j = 0; j < height; j++){
                    tileMap[i][j] = num;
                }
            }
        };

        void TileMapRoomFillTest(){
            for (int i = 0; i < width; i++){
                for (int j = 0; j < height; j++){
                    if ((i == 0 || i == width - 1) && j != height - 1){
                        tileMap[i][j] = 1;
                    }
                    else if ((i > 0 && i < width - 1) && (j > 0 && j < height - 1)){
                        tileMap[i][j] = 2;
                    }
                    else {
                        tileMap[i][j] = 0;
                    }
                }
            }
        };
};