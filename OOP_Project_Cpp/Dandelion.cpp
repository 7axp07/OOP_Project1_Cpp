#include "Dandelion.h"
#include "World.h"

Dandelion::Dandelion(int x, int y) : Plant('*', 0, x, y) {
}

void Dandelion::action() {
   for (int i = 0; i < 3; i++) {
       Plant::action();
   }
}

Organism* Dandelion::child() {
   return new Dandelion(*this);
}

int Dandelion::getColor() {
   return 3; 
}

/*
void Dandelion::collision(Organism* other) {
   world->addLog(this, "stepped on by " + std::string(1, other->getSymbol()));
}*/