#include "Grass.h"

Grass ::Grass(int x, int y) : Plant('w', 0, x, y) {

}

Organism* Grass::child() {
   return new Grass(*this);
}

int Grass::getColor() {
   return 2; 
}