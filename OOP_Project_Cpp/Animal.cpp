#include "Animal.h"
#include "World.h"
#include "Plant.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Animal::Animal(char symbol, int strenght, int initiative, int x, int y) : Organism(symbol, strenght, initiative, x, y) {

}

void Animal::action() {
    increaseAge();
    int mv = rand() % 8;
    while (!setPosition({ getX() + movement[mv][0], getY() + movement[mv][1] }, false)) {
        mv++;
        mv %= 8;
    }
}

void Animal::collision(Organism* other) {
    if (this == other) {
        return;
    }
    if (typeid(*this) == typeid(*other)) {
        if (getAge()<2 || other->getAge()<2) {
            return;
        }
        world->addLog(this, " reproduction..." );
        auto child = dynamic_cast<Animal*>(this)->child();
        int mv = rand() % 8;
        while (!child->setPosition({ getX() + movement[mv][0], getY() + movement[mv][1] }, true)) {
            mv++;
            if (mv > 8) {
                world->addLog(this, " Reproduction failed. No space :( .");
                return;
            }
        }
    }
    else if (isRunningAway() || other->isRunningAway()) {
        return;
    }
    else if (getStrength() > other->getStrength()) {
        world->addLog(this, " killed " + string(1, other->getSymbol()));
        other->kill();
    }
    else if (getStrength() < other->getStrength()) {
        world->addLog(this, " killed by " + string(1, other->getSymbol()));
        kill();
    }
    else {
        world->addLog(this, "Draw with " + string(1, other->getSymbol()));
        kill();
        other->kill();
    }
}

int Animal::getColor() {
    return 6;
}