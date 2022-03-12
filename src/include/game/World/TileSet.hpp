#include "game/World/Tile.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#pragma once
class TileSet {
    public:
        std::vector<Tile> tiles;

        int variants = 1;

        sf::Texture texture;

        std::vector<sf::Sprite> sprites;



        sf::Sprite GetSprite(int index){
            return sprites[tiles[index].sprite*variants];
        };

        sf::Sprite GetShadow(int index){
            return sprites[tiles[index].sprite*variants + 1];
        };

        sf::Sprite GetBottom(int index){
            return sprites[tiles[index].sprite*variants + 2];
        };


        int GetSpriteIndex(int index){
            return tiles[index].sprite*variants;
        };

        int GetShadowIndex(int index){
            return tiles[index].sprite*variants + 1;
        };

        int GetBottomIndex(int index){
            return tiles[index].sprite*variants + 2;
        };


        void AddTile(Tile tile){
            tiles.push_back(tile);
        };

        bool IsSolid(int index){
            return tiles[index].solid;
        };

        bool IsReflecting(int index){
            return tiles[index].reflecting;
        };

        int GetId(int index){
            return tiles[index].id;
        };

        void LoadTexture(const std::string path){
            texture.loadFromFile(path);
        };

        void GenerateSprites(int amount, int v){
            variants = v;
            for (int i = 0; i < amount; i++){
                for (int j = 0; j < variants; j++){
                    sf::Sprite s(texture, {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    sprites.push_back(s);
                }
            }
        };
};