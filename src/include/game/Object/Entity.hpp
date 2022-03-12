#include <vector>
#include "game/Object/CollisionBox.hpp"
#include "game/Object/HealthBar.hpp"
#include "game/Weapon/Bullet.hpp"
#include "game/Object/ObjectSprite.hpp"
#pragma once

class Entity {
    public:
        float x, y;
        sf::Vector2f velocity;
        bool bullet = false;
        bool invincible = false;
        int invincibilityFrames = 0;
        HealthBar HP;
        bool dead = false;
        std::vector<CollisionBox> collisionBoxes;
        std::vector<ObjectSprite> sprites;

        /*void Shoot(Bullet bullet){
            float Xvelocity = bullet.Xvelocity, Yvelocity = bullet.Yvelocity;

            int framesUntilEnergyLoss = bullet.framesUntilEnergyLoss;
            float energyLossEveryFrame = bullet.energyLossEveryFrame;

            float contactDamage = bullet.damage;
        };*/
        void Accelerate(int x, int y){
            velocity.x += x;
            velocity.y += y;
        };

        void AddSprite(sf::Sprite sprite, int Xoffset = 0, int Yoffset = 0){
            ObjectSprite s;
            s.sprite = sprite;
            s.offset.x = Xoffset;
            s.offset.y = Yoffset;
            sprites.push_back(s);
        };

        void Update(){
            int overall = 0;
            for (CollisionBox i : collisionBoxes){
                overall += i.damageTaken;
                i.damageTaken = 0;
            }
            if (!invincible || invincibilityFrames > 0){
                HP.Damage(overall);
                invincibilityFrames = (int) 1 / delta_time / 2;
            }
            if (HP.current == 0){
                Die();
            }
        };

        void Die(){
            dead = true;
        }
        
        bool CheckIfCollides(int offSet[2]){
            bool Xcollides = 0;
            bool Ycollides = 0;

            for (CollisionBox i : collisionBoxes){
                if (i.collidesWith >= 3){
                    
                };
            };
            return (Xcollides && Ycollides);
        };
};