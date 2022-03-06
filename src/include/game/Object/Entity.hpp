#include <vector>
#include "game/Object/CollisionBox.hpp"
#include "game/Object/HealthBar.hpp"
#include "game/Weapon/Bullet.hpp"

class Entity {
    public:
        float x, y;
        HealthBar HP;
        bool dead = false;
        std::vector<CollisionBox> collisionBoxes;

        /*void Shoot(Bullet bullet){
            float Xvelocity = bullet.Xvelocity, Yvelocity = bullet.Yvelocity;

            int framesUntilEnergyLoss = bullet.framesUntilEnergyLoss;
            float energyLossEveryFrame = bullet.energyLossEveryFrame;

            float contactDamage = bullet.damage;
        };*/

        void Update(){
            int overall = 0;
            for (CollisionBox i : collisionBoxes){
                overall += i.damageTaken;
                i.damageTaken = 0;
            };
            HP.Damage(overall);
            if (HP.current == 0){
                Die();
            };
        };

        void Die(){
            collisionBoxes = {};
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