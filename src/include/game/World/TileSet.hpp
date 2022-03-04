#include "game/World/Tile.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
class TileSet {
    public:
        std::vector<Tile> tiles;

        sf::Sprite GetSprite(int index){
            return tiles[index].sprite;
        };

        bool IsSolid(int index){
            return tiles[index].solid;
        };

        int GetId(int index){
            return tiles[index].id;
        };
};