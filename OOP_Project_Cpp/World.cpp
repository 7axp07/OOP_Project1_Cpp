#include "World.h"
#include <iostream>

World::World() : width(20), height(10), window(nullptr), statusWindow(nullptr) { 
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
    mvwprintw(startWin, 4, 1, "- Enter for next turn");

    mvwprintw(startWin, 6, 1, "Enter world width (5-40): ");
    wrefresh(startWin);
    echo();
    wscanw(startWin, "%d", &width);

    mvwprintw(startWin, 7, 1, "Enter world height (5-25): ");
    wrefresh(startWin);
    wscanw(startWin, "%d", &height);
    noecho();

    if (width < 5 || width > 50) {
        width = 20; 
    }
    if (height < 5 || height > 50) {
        height = 10; 
    }

    mvwprintw(startWin, 9, 1, "Press any key to start...");
    wrefresh(startWin);
    wgetch(startWin);
    delwin(startWin);
    clear();
    refresh();

    allocateGrid();
    clearGrid();
    window = newwin(height + 2, width + 2, 0, 0); 
    statusWindow = newwin(5, 50, height + 2, 0); 
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

void World::addOrganism(Organism* organism) {
    organisms.push_back(organism);
}

void World::executeTurn() {
    lastAction = ""; 
    for (Organism* organism : organisms) {
        organism->action();
        lastAction += "Organism at (" + std::to_string(organism->getX()) + ", " +
                      std::to_string(organism->getY()) + ") moved.\n";
    }
    for (Organism* organism : organisms) {
        organism->increaseAge();
    }
}
void World::updateStatus(const std::string& status) {
    werase(statusWindow); 
    mvwprintw(statusWindow, 1, 1, "Author: AP, Index: 203194");
    mvwprintw(statusWindow, 2, 1, "^ v < > - Move, P - Quit, Enter - Next Turn");
    mvwprintw(statusWindow, 4, 1, "Action: %s", status.c_str());
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
    updateStatus(lastAction);
}

