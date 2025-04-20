#include "Hogweed.h"
#include "World.h"
#include "Animal.h"

Hogweed::Hogweed(int x, int y) : Plant('Y', 10, x, y) {
}

int Hogweed::getColor() {
    return 2; 
}

Organism* Hogweed::child() {
    return new Hogweed(*this);
}

void Hogweed::collision(Organism* other) {
    world->addLog(this, "poisoned " + string(1, other->getSymbol()));
    other->kill();
    kill(); // not sure about this one 100%
}

void Hogweed::action() {
   for (size_t i = 0; i < 8; i++){
    Organism* neighbor = world->getOrganismAt({this->getX() + movement[i][0], this->getY() + movement[i][1]});
    if (neighbor != nullptr) {
        bool isAnimal = dynamic_cast<Animal*>(neighbor);
        if (isAnimal) {
            world->addLog(this, " has poisoned "+ std::string(1, neighbor->getSymbol()));
            neighbor->kill();
        }
    }
   }
   
}
