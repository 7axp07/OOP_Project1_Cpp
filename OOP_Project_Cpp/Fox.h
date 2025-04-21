#include "Animal.h"

class Fox : public Animal {
public:
    Fox(int x, int y);
    int getColor();
    Organism* child();
    void action();
};