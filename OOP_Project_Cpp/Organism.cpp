#include <string>
#include <iostream>
#include "Organism.h"
#include "World.h"
#include "Plant.h"
using namespace std;

Organism::Organism(char symbol, int strength, int initiative, int x, int y) {
    this->world = World::getInstance();
    this->symbol = symbol;
    this->strength = strength;
    this->initiative = initiative;
    this->position = { x, y };
    this->age = 0;
    world->addOrganism(this);
}

Organism::Organism(const Organism& a) {
    this->world = a.world;
    this->symbol = a.symbol;
    this->strength = a.strength;
    this->initiative = a.initiative;
    this->position = a.position;
    this->age = 0;
    world->addOrganism(this);
}

bool Organism::isRunningAway() {
    return false;
}

int Organism::priority(Organism* a, Organism* b) {
    if (a->getInitiative() > b->getInitiative()) {
        return 1;
    }
    else if (a->getInitiative() < b->getInitiative()) {
        return 0;
    }
    else {
        if (a->age > b->age) {
            return 1;
        }

        else {
            return 0;
        }
    }
}

string Organism::toString() {
    string output;
    output += typeid(*this).name();
    output += ";";
    output += to_string(position.first);
    output += ";";
    output += to_string(position.second);
    output += ";";
    output += to_string(strength);
    output += ";";
    output += to_string(initiative);
    output += ";";
    output += to_string(age);
    output += ";";
    return output;
}

//gettery
char Organism::getSymbol() {
    return symbol;
}
int Organism::getStrength() {
    return strength;
}
int Organism::getInitiative() {
    return initiative;
}
int Organism::getAge() {
    return age;
}
//

int Organism::getX() {
    return position.first;
}
int Organism::getY() {
    return position.second;
}



bool Organism::setPosition(pair<int, int> pos, bool requireEmpty) {
    if (pos.first < 0 || pos.first >= world->getWidth() || pos.second < 0 || pos.second >= world->getHeight()) {
        return false; 
    }
    if (requireEmpty && world->getOrganismAt(pos) != nullptr) {
        return false; 
    }

    prevPosition = position;
    Organism* other = world->getOrganismAt(pos);
    this->position = pos;
    if (dynamic_cast<Plant*>(this)) {
        world->addLog(this, "spread to " + to_string(pos.first) + "," + to_string(pos.second));
    }
    else {
        world->addLog(this, "moved to " + to_string(pos.first) + "," + to_string(pos.second));
    }
    if (other != nullptr) {
        other->collision(this); 
    }
    return true;
}

//

void Organism::increaseAge(int value) {
    age += value;
}
void Organism::increaseStrength(int value) {
    strength += value;
}

void Organism::goBack() {
    if (prevPosition.first != -1 && prevPosition.second != -1) {
        position = prevPosition;
        world->addLog(this, "moved back to " + to_string(prevPosition.first) + "," + to_string(prevPosition.second));
    }
}

void Organism::kill() {
   position = { -1, -1 };
   strength = -1;
   initiative = -1;
}

int Organism::getColor() {
    return 7; 
}





