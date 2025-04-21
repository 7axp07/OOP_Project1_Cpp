#include "Guarana.h"
#include "World.h"

Guarana::Guarana(int x, int y) : Plant('g', 0, x, y) {
}

int Guarana::getColor() {
    return 1; 
}

Organism* Guarana::child() {
    return new Guarana(*this);
}

void Guarana::collision(Organism* other) {
    other->increaseStrength(3);
    world->addLog(this, " strengthened " + std::string(1, other->getSymbol()));
    kill();
}