#include "SFML/Graphics.hpp"
#include <math.h>

std::vector<sf::Texture> HPtextures;

class HealthBar{
    public:
        int current = 0;
        int max = 10;

        int texture;

        int spritesAmount;

        sf::Vector2i spriteSize;

        sf::Sprite currentSprite;

        void Damage(int amt){
            if (current - amt < 0){
                current = 0;
            }
            else if (current - amt > max){
                current = max;
            }
            else{
                current -= amt;
            }
        }

        void setTexture(int s){
            texture = s;
        }

        float GetPercent(){
            return (float)current / max;
        }

        void UpdateSprite(){
            float c = floor((float)spritesAmount * GetPercent()) * spriteSize.x - spriteSize.x;
            currentSprite.setTextureRect({(int)c, 0, spriteSize.x, spriteSize.y});
        }
};