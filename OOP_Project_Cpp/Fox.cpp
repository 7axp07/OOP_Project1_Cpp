#include "Fox.h"
#include "World.h"

Fox::Fox(int x, int y) : Animal('V', 3, 7, x, y) {
}

int Fox::getColor() {
    return 9; 
}

Organism* Fox::child() {
    return new Fox(getX(), getY());
}

void Fox::action(){
    increaseAge();
    int mv = rand() % 8;
    pair <int, int> newPos;
    while (mv < 8){
        newPos = { getX() + movement[mv][0], getY() + movement[mv][1] };
        if (world->getOrganismAt(newPos) == nullptr) {
            if (setPosition(newPos, false)) {
                break;
            }
        }
        else if (world->getOrganismAt(newPos)->getStrength() <= getStrength()) {
            if (setPosition(newPos, false)) {
                break;
            }
        }
        else if (world->getOrganismAt(newPos)->getStrength() > getStrength()) {
            world->addLog(this, " sensed danger from " + string(1, world->getOrganismAt(newPos)->getSymbol()));
            return;
        }
        mv++;
    }
}