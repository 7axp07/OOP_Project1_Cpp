#pragma once
#include "Animal.h"

class Human : public Animal {
    private :
    int ability;
    bool abilityUsed;
    pair<int, int> dir;

public:
    Human(int x, int y);
    void action();
    void collision(Organism* other);
    int getColor();
    void ability();

};