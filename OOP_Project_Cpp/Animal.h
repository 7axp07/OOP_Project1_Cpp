#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(char symbol, int strength, int initiative, int x, int y) : Organism(symbol, strength, initiative, x, y) {}
    virtual void action();
    virtual void collision(Organism* other);
};