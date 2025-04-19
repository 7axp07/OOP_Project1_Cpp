#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <ncurses.h>
#include "Organism.h"

class World {
private:
    int width, height;
    std::vector<Organism*> organisms;
    char** grid;
    WINDOW* window;       // Ncurses window for the grid
    WINDOW* statusWindow; // Ncurses window for the status
    std::string lastAction; // Stores the last action for status display

    void allocateGrid();
    void deallocateGrid();
    void clearGrid();

public:
    World();
    ~World();

    void startScreen(); // Displays the start screen
    void addOrganism(Organism* organism);
    void executeTurn();
    void drawWorld();
    void updateStatus(const std::string& status); // Updates the status window
};

#endif // WORLD_H