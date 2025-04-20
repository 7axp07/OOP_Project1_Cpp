#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <list>
#include <string>
#include <ncurses.h>
#include "Organism.h"
using namespace std;

class World {
private:
    int width, height;
    list<Organism*> organisms;
    char** grid;
    WINDOW* window;      
    WINDOW* statusWindow; 
    string lastAction; 
    static World* instance;
    int logCount;
    int turn;

    void allocateGrid();
    void deallocateGrid();
    void clearGrid();
    void clearLog();

public:
    World();
    ~World();

    //functionalities
    void startScreen(); 
    void addOrganism(Organism* organism);
    void executeTurn();
    void drawWorld();
    void updateStatus(); 
    void addLog(Organism* organism, string action);
    void sortOrganisms();
    void initialPopulate();
    void initializeColors();


    //getsets
    static World* getInstance();
    static World* getInstance(int width, int height);
    int getWidth();
    int getHeight();
    Organism* getOrganismAt(pair<int, int> pos);
    void removeOrganism(Organism* organism);
};

#endif // WORLD_H