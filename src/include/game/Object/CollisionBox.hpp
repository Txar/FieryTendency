#pragma once

bool collisionCheck(int x, int y, int width, int height, int x2, int y2, int width2, int height2){
    sf::IntRect a, b;

    a.left = x;
    a.top = y;
    a.width = width;
    a.height = height;

    b.left = x2;
    b.top = y2;
    b.width = width2;
    b.height = height2;

    return a.intersects(b);
};

class CollisionBox {
    public:
        sf::Vector2i offset = {0, 0};

        float x = 0, y = 0;
        int width = 32, height = 32;
        //int hits = 2; //0 is players/enemies, 1 is bullets, 2 is both, 3 is tiles, 4 is all
        int damageTaken = 0;
 
        bool CheckIfCollidesWith(CollisionBox boxB) {
	        return collisionCheck(x + offset.x, y + offset.y, width, height, boxB.x + boxB.offset.x, boxB.y + boxB.offset.x, boxB.width, boxB.height);
        };
};