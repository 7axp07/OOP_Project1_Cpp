#include "World.h"
#include <iostream>

World::World() : width(20), height(10), window(nullptr), statusWindow(nullptr), logCount(0), turn(0) { 
    initscr();
    noecho();
    curs_set(0);
}

World::~World() {
    deallocateGrid();

    for (Organism* organism : organisms) {
        delete organism;
    }

    if (window) {
        delwin(window);
    }
    if (statusWindow) {
        delwin(statusWindow);
    }
    endwin();
}

void World::startScreen() {
    WINDOW* startWin = newwin(100, 50, 0, 0);

    mvwprintw(startWin, 1, 1, "Simulation game :)");
    mvwprintw(startWin, 2, 1, "- Arrow keys to move Human");
    mvwprintw(startWin, 3, 1, "- 'p' to quit");
    mvwprintw(startWin, 4, 1, "- 'e' for ability");
    mvwprintw(startWin, 5, 1, "- Enter for next turn");

    mvwprintw(startWin, 7, 1, "Enter world width (5-40): ");
    wrefresh(startWin);
    echo();
    wscanw(startWin, "%d", &width);

    mvwprintw(startWin, 8, 1, "Enter world height (5-25): ");
    wrefresh(startWin);
    wscanw(startWin, "%d", &height);
    noecho();

    if (width < 5 || width > 50) {
        width = 20; 
    }
    if (height < 5 || height > 50) {
        height = 10; 
    }

    mvwprintw(startWin, 10, 1, "Press any key to start...");
    wrefresh(startWin);
    wgetch(startWin);
    delwin(startWin);
    clear();
    refresh();

    allocateGrid();
    clearGrid();
    window = newwin(height + 2, width + 2, 0, 0); 
    statusWindow = newwin(10, 50, height + 2, 0); 
    wrefresh(window);
    wrefresh(statusWindow);
}


void World::allocateGrid() {
    grid = new char*[height];
    for (int i = 0; i < height; ++i) {
        grid[i] = new char[width];
    }
}

void World::deallocateGrid() {
    if (grid) {
        for (int i = 0; i < height; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }
}

void World::clearGrid() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            grid[i][j] = ' ';
        }
    }
}
void World::clearLog() {
    werase(statusWindow);
    mvwprintw(statusWindow, 1, 1, "Author: AP, Index: 203194");
    mvwprintw(statusWindow, 2, 1, "^ v < > - Move, P - Quit, Enter - Next Turn");
    logCount = 0;
    //mvwprintw(statusWindow, 4, 1, "Action: ");
    wrefresh(statusWindow);
}
void World::addLog(Organism* source, string log) {
    string sourceName = typeid(*source).name(); 
    sourceName = source->draw() + string("(") + sourceName.substr(6) + ")"; 

    logCount++; 
    if (logCount > 5) { 
        clearLog();
    }
    mvwprintw(statusWindow, 3 + logCount, 1, "%s %s", sourceName.c_str(), log.c_str());
    wrefresh(statusWindow);
}

void World::addOrganism(Organism* organism) {
    organisms.push_back(organism);
}

void World::sortOrganisms() {
    organisms.sort(Organism::priority);
}

void World::executeTurn() {
    clearLog(); 
    turn++;
    sortOrganisms();
    for (Organism* o : organisms) {
        if (o->getStrength() > -1){
            o->action();
        }
        else { break; }
    }
}
void World::updateStatus() {
    mvwprintw(statusWindow, 1, 1, "Author: AP, Index: 203194");
    mvwprintw(statusWindow, 2, 1, "^ v < > - Move, P - Quit, Enter - Next Turn");
   // mvwprintw(statusWindow, 3, 1, "Action: %s", status.c_str());
    wrefresh(statusWindow);
}

void World::drawWorld() {
    clearGrid();
    for (Organism* organism : organisms) {
        grid[organism->getY()][organism->getX()] = organism->draw();
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            mvwaddch(window, i + 1, j + 1, grid[i][j]);
        }
    }
    box(window, 0, 0);
    wrefresh(window);
    updateStatus();
}

World* World::getInstance() {
    static World instance;
    return &instance;
}
int World::getWidth() {
    return width;
}
int World::getHeight() {
    return height;
}

Organism* World::getOrganismAt(pair<int, int> pos) {
    for (Organism* organism : organisms) {
        if (organism->getX() == pos.first && organism->getY() == pos.second) {
            return organism;
        }
    }
    return nullptr;
}

void initialPopulate() {
    // Add initial organisms to the world
    // Example: addOrganism(new Wolf(5, 5, this));
    // Example: addOrganism(new Grass(10, 10, this));
}
