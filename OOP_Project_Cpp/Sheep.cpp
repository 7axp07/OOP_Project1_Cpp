#include "Sheep.h"
#include "World.h"

Sheep::Sheep(int x, int y) : Animal('@', 4, 4, x, y) {
}

int Sheep::getColor() {
    return 7; 
}

Organism* Sheep::child() {
    return new Sheep(getX(), getY());
}