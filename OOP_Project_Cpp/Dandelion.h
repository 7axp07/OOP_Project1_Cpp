#pragma once
#include "Plant.h"

class Dandelion : public Plant {
public:
    Dandelion(int x, int y);
    void action();
    Organism* child();
    int getColor();
   // void collision(Organism* other);
};