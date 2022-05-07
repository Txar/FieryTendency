#include <vector>
#include "game/Object/CollisionBox.hpp"
#include "game/Object/HealthBar.hpp"
#include "game/Weapon/Bullet.hpp"
#include "game/Object/ObjectSprite.hpp"
#include "game/Object/Loot.hpp"
#pragma once

class Entity {
    public:
        float x, y;
        sf::Vector2f velocity;
        int invincibilityFrames = 0;
        float invincibilityTimer;
        int team = 0; //0 is players, 1 is enemies
        HealthBar HP;

        bool dead = false;
        bool justDied = false;

        std::vector<CollisionBox> collisionBoxes;
        std::vector<ObjectSprite> sprites;
        std::vector<ObjectSprite> dead_sprites;

        std::vector<ItemDrop> loot;

        ObjectSprite HPsprite;

        bool player = false;

        //bullet stuff
        std::vector<TrailPoint> trailPoints;
        sf::Sprite trailSprite;
        int piercing;
        int bounces;
        float collisionDamage;
        bool bullet = false;
        bool floating = false;
        bool invincible = false;
        bool item = false;

        Entity(){
            HP.current = 1;
            HP.max = 1;
        }

        void Accelerate(float x, float y){
            velocity.x += x;
            velocity.y += y;
        }

        void AddSprite(sf::Sprite sprite, int Xoffset = 0, int Yoffset = 0){
            ObjectSprite s;
            s.sprite = sprite;
            s.offset.x = Xoffset;
            s.offset.y = Yoffset;
            sprites.push_back(s);
        }

        void AddDeadSprite(sf::Sprite sprite, int Xoffset = 0, int Yoffset = 0){
            ObjectSprite s;
            s.sprite = sprite;
            s.offset.x = Xoffset;
            s.offset.y = Yoffset;
            sprites.push_back(s);
        }

        void UpdateHealthBarSprite(){
            HPsprite.sprite = HP.currentSprite;
            HPsprite.offset.x = - HP.spriteSize.x / 4;
            HPsprite.offset.y = - ceil(TILE_SIZE / 1.5);
        }

        void UpdateTrail(){
            for (int i = 0; i < (int)trailPoints.size(); i++){
                if (trailPoints.at(i).timer <= 0){
                    trailPoints.erase(trailPoints.begin() + i);
                }
                else {
                    trailPoints.at(i).timer -= delta_time;
                }
            }
        }

        void Update(){
            for (int i = 0; i < (int)collisionBoxes.size(); i++){
                collisionBoxes.at(i).x = x;
                collisionBoxes.at(i).y = y;
            }

            if (!bullet){
                int overall = 0;

                for (int i = 0; i < (int)collisionBoxes.size(); i++){
                    overall += collisionBoxes.at(0).damageTaken;
                    collisionBoxes.at(i).damageTaken = 0;
                }

                if (invincibilityTimer > 0){
                    invincibilityTimer -= delta_time;
                }

                if (!invincible && invincibilityTimer <= 0 && overall != 0){
                    HP.Damage(overall);
                    invincibilityTimer = 0.5;
                }
                if (HP.current == 0){
                    Die();
                }
                HP.UpdateSprite();
                UpdateHealthBarSprite();
            }
        }

        void Die(){
            dead = true;
            justDied = true;
        }

        void AccelerateTowards(Entity target, sf::Vector2f v){
            float tx = target.x - x;
            float ty = target.y - y;
            Accelerate(tx / abs(tx) * v.x, ty / abs(ty) * v.y);
        }
};