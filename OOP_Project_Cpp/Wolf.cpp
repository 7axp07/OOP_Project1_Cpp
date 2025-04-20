#include "Wolf.h"
#include "World.h"

Wolf::Wolf(int x, int y) : Animal('W', 9, 5, x, y) {

}

int Wolf::getColor() {
    return 8;
}

Organism* Wolf::child() {
    return new Wolf(getX(), getY());
}