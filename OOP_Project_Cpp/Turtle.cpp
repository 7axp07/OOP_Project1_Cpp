#include "Turtle.h"
#include "World.h"

Turtle::Turtle(int x, int y) : Animal('#', 2, 1, x, y) {
}

int Turtle::getColor() {
    return 11; 
}

Organism* Turtle::child() {
    return new Turtle(*this);
}

void Turtle::action(){
    bool move = rand() % 100 >= 75;
    if (move){
        Animal::action();
    }
    else {increaseAge();}
}

void Turtle::collision(Organism* other) {
    if (other == this) {
        return; 
    }
    if (other->getStrength() < 5) {
        world->addLog(this, " repelled " + std::string(1, other->getSymbol()));
        other->goBack();
    }
    else {
        Animal::collision(other);
    }
}