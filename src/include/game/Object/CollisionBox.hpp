#pragma once

bool collisionCheck(float x, float y, int width, int height, float x2, float y2, int width2, int height2){
    bool Xcollides = false;
    bool Ycollides = false;

    for (int i = 0; i != 2; i++){
	    for (int j = 0; j != 2; j++){

		    if (x2 + width2 * i  >= x && x + width2 * i <= x + width) {
		        Xcollides = true;
            };

    		if (y2 + height2 * j >= y && y2 + height2 * j <= y + height){
				Ycollides = true;
            };

        };
    };
    return (Xcollides && Ycollides);
};

class CollisionBox {
    public:
        float x = 0, y = 0;
        int width = 32, height = 32;
        int collidesWith = 2; //0 is players/enemies, 1 is bullets, 2 is both, 3 is tiles, 4 is all
        int damageTaken = 0;

        int offSetFromEntity[2] = {0, 0};

        bool CheckIfCollidesWith(CollisionBox boxB) {
	        return collisionCheck(x, y, width, height, boxB.x, boxB.y, boxB.width, boxB.height);
        };

};