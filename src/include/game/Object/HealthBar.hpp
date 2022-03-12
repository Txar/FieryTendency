#include <math.h>

class HealthBar{
    public:
        int current = 0;
        int max = 10;

        void Damage(float amt){
            if (current - amt < 0){
                current = 0;
            }
            else if (current - amt > max){
                current = max;
            }
            else{
                current -= amt;
            }
        };

        int GetPercent(){
            return ceil(current / max);
        };
};