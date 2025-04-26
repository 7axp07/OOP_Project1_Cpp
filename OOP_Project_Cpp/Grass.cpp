#include "Grass.h"
#include "World.h"

Grass ::Grass(int x, int y) : Plant('w', 0, x, y) {

}

Organism* Grass::child() {
   return new Grass(*this);
}

int Grass::getColor() {
   return 2; 
}

//not sure about this one

/*
void Grass::collision(Organism* other) {
   world->addLog(this, "stepped on by " + std::string(1, other->getSymbol()));
}*/