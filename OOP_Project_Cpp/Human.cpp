#include "Human.h"
#include "World.h"

Human::Human(int x, int y) : Animal('&', 5, 4, x, y) {
    ability = -5;
    dir = { 0, 0 };
}

int Human::getColor() {
    return 5; 
}

void Human::action(){
    increaseAge();
    if (ability > 0) { 
        for (int i = 0; i < 8; i++) {
            pair<int, int> pos = { getX() + movement[i][0], getY() + movement[i][1] };
            Organism* org = world->getOrganismAt(pos);
            if (org != nullptr) {
                world->addLog(this, " burned " + string(1, org->getSymbol()));
                org->kill();
            }
        }
        ability--; 
    }
    else if (ability < 0) { 
        ability++; 
    }
    setPosition({getX() + dir.first, getY() + dir.second}, true);
    world->addLog(this, " moved to (" + to_string(getX()) + ", " + to_string(getY()) + ")");
    
    dir = {0,0};

}


bool Human::setDir(pair<int, int> dir) {
    if (dir.first == 0 && dir.second == 0) {
        return false;
    }
    this->dir = dir;
    return true;
}

//ability

void Human::startAbility() {
    if (ability == 0) { 
        ability = 5; 
        world->addLog(this, "Activated Ability: Arson.");
    }
    else if (ability > 0) {
        world->addLog(this, "Ability is already active.");
    }
    else {
        world->addLog(this, "Ability is on cooldown.");
    }
}

Organism* Human::child(){
    return nullptr;
}
 
