#include "World.h"
#include "Organism.h"
#include "Human.h"
#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));
    World* world = World::getInstance(); 
    world->startScreen();
    world->initialPopulate();
    bool running = true;
    world->drawWorld();
    while (running) {
        Human* human = dynamic_cast<Human*>(world->getHuman());
 
        int ch = getch(); 
        switch (ch) {
            case 'p': 
            case 'P':
                running = false;
                break;
            case 'w': 
            case 'W':
            human->setDir({0, -1});
            continue;
            case 's':
            case 'S':
            human->setDir({0, 1});
            continue;
            case 'a':
            case 'A':
            human->setDir({-1, 0});
            continue;
            case 'd':
            case 'D':
            human->setDir({1, 0});
            continue;
            case 'q':
            case 'Q':
                human->startAbility();
                continue;
            case KEY_ENTER: 
            case '\n': 
                world->executeTurn(); 
                world->drawWorld(); 
                break;
            default:
                continue;
        }

      //  world->drawWorld();    
      //  world->executeTurn();

    }
    endwin();
    return 0;
}