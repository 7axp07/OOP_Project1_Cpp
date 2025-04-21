#include "Animal.h"

class Turtle : public Animal {
public:
    Turtle(int x, int y);
    void action();
    void collision(Organism* other);
    int getColor();
    Organism* child();
};