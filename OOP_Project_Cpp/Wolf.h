#include "Animal.h"

class Wolf : public Animal {
    public:
        Wolf(int x, int y);
        int getColor();
        Organism* child();
};