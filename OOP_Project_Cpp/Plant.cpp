#include "Plant.h"
#include "World.h"
#include <iostream>
using namespace std;

Plant::Plant(char symbol, int strength, int x, int y) : Organism(symbol, strength, 0, x, y) {
    
}

void Plant::action() {
    bool spread = rand() % 100 == 0; 
    if (spread) {
        auto child = dynamic_cast<Plant*>(this->child());
        int mv = rand() % 8;
        bool placed = false;

        for (int i = 0; i < 8; ++i) {
            int newX = this->getX() + movement[mv % 8][0];
            int newY = this->getY() + movement[mv % 8][1];
            if (child->setPosition({newX, newY}, true)) {
                placed = true;
                break;
            }
            mv++;
        }

        if (!placed) {
            world->addLog(this, "Failed to spread.");
            world->removeOrganism(child);
            delete child; 
            child = nullptr;
        } else {
            world->addOrganism(child);
            world->addLog(this, "Spread its seeds!");
        }
    }
}

void Plant::collision(Organism* other) {
    if (this == other) {
        return;
    }
    if (other->getStrength() < this->getStrength()) {
        world->addLog(this, "poisoned " + string(1, other->getSymbol()));
        other->kill();
    }
    else if (other->getStrength() > this->getStrength()) {
        world->addLog(this, "trampled by " + string(1, other->getSymbol()));
        this->kill();
    }
    else {
        world->addLog(this, "Draw with " + string(1, other->getSymbol()));
        this->kill();
        other->kill();
    }
}

int Plant::getColor() {
    return 2; 
}