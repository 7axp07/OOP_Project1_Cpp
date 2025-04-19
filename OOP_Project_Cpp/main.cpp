#include "World.h"
#include "Organism.h"
#include <ncurses.h>

int main() {
    World world;
    world.startScreen();

    // Add organisms
    // Example: world.addOrganism(new Wolf(5, 5, &world));
    // Example: world.addOrganism(new Grass(10, 10, &world));

    bool running = true;
    while (running) {
        world.drawWorld();    
        world.executeTurn();  

        int ch = getch(); 
        switch (ch) {
            case 'p': 
            case 'P':
                running = false;
                break;
            case KEY_ENTER:
            case KEY_UP: 
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                
                break;
            default:
                break;
        }
    }

    return 0;
}