#pragma once
#include "Plant.h"

class Wolfberry : public Plant {
    
    public:
    Wolfberry(int x, int y);
    void collision(Organism* other) ;
    int getColor();
    Organism* child();
};

// tak naprawdę wolfberry =/= wilcze jagody tylko belladonna ale niech już będzie....