#include "Guarana.h"
#include "World.h"

Guarana::Guarana(int x, int y) : Plant('o', 0, x, y) {
}

int Guarana::getColor() {
    return 1; 
}

Organism* Guarana::child() {
    return new Guarana(*this);
}

void Guarana::collision(Organism* other) {
    world->addLog(this, "strengthened " + other->getSymbol());
    other->increaseStrength(3);
    kill();
}