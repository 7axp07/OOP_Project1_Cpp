#include "Antylopa.h"
#include "World.h"

Antylopa::Antylopa(int x, int y) : Animal('Y', 4, 4, x, y) {
}

int Antylopa::getColor() {
    return 10; 
}
Organism* Antylopa::child() {
    return new Antylopa(*this);
}

void Antylopa::action() {
    increaseAge();
    int mv = rand() % 16;
    for (int i = 0; i < 2; i++){
        int mv = rand() % 8;
        while (!setPosition({ getX() + movement[mv][0], getY() + movement[mv][1] }, false)) {
            mv++;
            mv %= 8;
        }
    }
}


bool Antylopa::isRunningAway() {
    bool isRunAway = rand() % 2; 
    if (isRunAway) {
        for (int i = 0; i < 8; ++i) { 
            int newX = getX() + movement[i][0];
            int newY = getY() + movement[i][1];
            if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight() &&
                world->getOrganismAt({newX, newY}) == nullptr) {
                setPosition({newX, newY}, false); 
                world->addLog(this, "escaped to " + std::to_string(newX) + ", " + std::to_string(newY));
                return true;
            }
        }
    }
    return false; 
}

void Antylopa::collision(Organism* other) {
    if (isRunningAway()) {
        return; 
    }
    Animal::collision(other);
}