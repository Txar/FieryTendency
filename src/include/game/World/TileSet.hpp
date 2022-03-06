#include "game/World/Tile.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#pragma once
class TileSet {
    public:
        std::vector<Tile> tiles;

        sf::Texture texture;

        std::vector<sf::Sprite> sprites;

        sf::Sprite GetSprite(int index){
            return sprites[tiles[index].sprite];
        };

        void AddTile(Tile tile){
            tiles.push_back(tile);
        };

        bool IsSolid(int index){
            return tiles[index].solid;
        };

        int GetId(int index){
            return tiles[index].id;
        };

        void LoadTexture(const std::string path){
            texture.loadFromFile(path);
        };

        void GenerateSprites(int amount, int variants){
            for (int i = 0; i < amount; i++){
                for (int j = 0; j < variants; j++){
                    sf::Sprite s(texture, {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    sprites.push_back(s);
                }
            }
        };
};