#include "Wolfberry.h"
#include "World.h"

Wolfberry::Wolfberry(int x, int y) : Plant('o', 99, x, y) {
}

int Wolfberry::getColor() {
    return 4; 
}

Organism* Wolfberry::child() {
    return new Wolfberry(*this);
}

void Wolfberry::collision(Organism* other) {
    world->addLog(this, "poisoned " + string(1, other->getSymbol()));
    other->kill(); 
    kill();
}