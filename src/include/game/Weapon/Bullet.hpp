#include "game/Weapon/Weapon.hpp"
#include <vector>

class Bullet {
    public:
        float Xvelocity, Yvelocity;
        
        //this class is gonna be useful for some weird cool bullet types
        float damage = 0;
        int framesUntilEnergyLoss = 120;
        float energyLossEveryFrame = 1/60;

        void SetDamage(std::vector<Attack> cycle, int slot){
            damage = cycle[slot].damage;
        }
};