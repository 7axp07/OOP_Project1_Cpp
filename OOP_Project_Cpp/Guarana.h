#pragma once
#include "Plant.h"

class Guarana : public Plant {
    
    public:
    Guarana(int x, int y);
    void collision(Organism* other) ;
    int getColor();
    Organism* child();
};