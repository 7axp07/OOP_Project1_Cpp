#pragma once
#include "Organism.h"

class Plant : public Organism {
public:
    Plant(char symbol, int strength, int x, int y);
    virtual void action();
    virtual void collision(Organism* other);
    virtual int getColor();
};