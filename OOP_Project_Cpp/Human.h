#pragma once
#include "Animal.h"

class Human : public Animal {
    private :
    int ability;
    bool abilityUsed;
    pair<int, int> dir;

public:
    Human(int x, int y);
    void action() override;
   // void collision(Organism* other) override;
    int getColor() override;

    Organism* child() override;

    void startAbility();
    void setAbility();

    bool setDir(pair<int, int> dir);

};