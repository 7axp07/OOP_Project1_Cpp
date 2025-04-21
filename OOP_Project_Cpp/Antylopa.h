#include "Animal.h"

class Antylopa : public Animal {
public:
    Antylopa(int x, int y);
    int getColor();
    Organism* child();
    void action();
    bool isRunningAway();
    void collision(Organism* other);
};


// jedyna z polską nazwą bo angielską nazwe dziwnie sie pisze