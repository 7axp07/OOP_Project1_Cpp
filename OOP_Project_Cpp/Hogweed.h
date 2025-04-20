#pragma once
#include "Plant.h"

class Hogweed : public Plant {
    
    public:
    Hogweed(int x, int y);
    void action();
    void collision(Organism* other) ;
    int getColor();
    Organism* child();
};
