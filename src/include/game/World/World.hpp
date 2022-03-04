#include "game/World/TileSet.hpp"
#include <vector>
#include "game/Object/Entity.hpp"

class World {
    public:
        int width;
        int height;
        int tileMap[1][1];
        std::vector<Entity> objectMap = {};
        
        void InitializeTileMap(int w, int h, TileSet tiles){
            TileSet pallete = tiles;
            width = w, height = h;

            int tileMap[width][height];
        };

        int SummonObject(Entity object){
            int index = objectMap.size();
            objectMap.push_back(object);
            return index;
        };

        int IsASolid(int x, int y){
            
        };
};