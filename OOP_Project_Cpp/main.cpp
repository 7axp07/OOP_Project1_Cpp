#include "World.h"
#include "Organism.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));
    World* world = World::getInstance(); 
    world->startScreen();
    world->initialPopulate();
    bool running = true;
    while (running) {
        world->drawWorld();    
        world->executeTurn();

        int ch = getch(); 
        switch (ch) {
            case 'p': 
            case 'P':
                running = false;
                break;
            case KEY_ENTER:
                break;
            case KEY_UP: 
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                break;
        }
    }
    endwin();
    return 0;
}