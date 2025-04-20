#include "World.h"
#include "Organism.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Wolfberry.h"
#include "Hogweed.h"
#include "Wolf.h"
#include <iostream>
#include <ncurses.h>

World::World() : width(20), height(10), window(nullptr), statusWindow(nullptr), logCount(0), turn(0) { 
    initscr();
    start_color();
    initializeColors();
    noecho();
    curs_set(0);
    allocateGrid(); 
    clearGrid();   

    window = newwin(height + 2, width + 2, 0, 0); 
    statusWindow = newwin(10, 50, height + 2, 0); 
    wrefresh(window);
    wrefresh(statusWindow);
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
    std::cout << "Terminal restored." << std::endl;
}

void World::initializeColors() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
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
        grid = nullptr;
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
    mvwprintw(statusWindow, 3, 1, "Turn: %d", turn); 
    logCount = 0;
    wrefresh(statusWindow);
}
void World::addLog(Organism* source, string log) {
    if (source == nullptr) {
        return; 
    }
    string sourceName(1, source->getSymbol());
    logCount++; 
    if (logCount > 10) { 
        clearLog();
    }
    mvwprintw(statusWindow, 4 + logCount, 1, "%s %s", sourceName.c_str(), log.c_str());
    wrefresh(statusWindow);
}

void World::addOrganism(Organism* organism) {
    for (Organism* existing : organisms) {
        if (existing == organism) {
            return;
        }
    }
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
    mvwprintw(statusWindow, 3, 1, "Turn: %d", turn); 
    wrefresh(statusWindow);
}

void World::drawWorld() {
    clearGrid();
    for (Organism* organism : organisms) {
        int x = organism->getX();
        int y = organism->getY();
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = organism->getSymbol();
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char symbol = grid[i][j];
            int colorPair = 7; 
            Organism* organism = getOrganismAt({j, i});
            if (organism) {
                colorPair = organism->getColor();
            }
            wattron(window, COLOR_PAIR(colorPair));
            mvwaddch(window, i + 1, j + 1, symbol);
            wattroff(window, COLOR_PAIR(colorPair));
        }
    }
    box(window, 0, 0);
    wrefresh(window);
    updateStatus();
}

World* World::instance = nullptr;

World* World::getInstance() {
    if (instance == nullptr) {
        instance = new World(); 
    }
    return instance;
}

int World::getWidth() {
    return width;
}

int World::getHeight() {
    return height;
}

Organism* World::getOrganismAt(pair<int, int> pos) {
    if (pos.first < 0 || pos.first >= width || pos.second < 0 || pos.second >= height) {
        return nullptr; 
    }
    for (Organism* organism : organisms) {
        if (organism->getX() == pos.first && organism->getY() == pos.second) {
            return organism;
        }
    }
    return nullptr;
}

void World::removeOrganism(Organism* organism) {
    organisms.remove(organism); 
}

void World::initialPopulate() {

    new Grass(rand()% width, rand()% height);
    new Dandelion(rand()% width, rand()% height);
    new Guarana(rand()% width, rand()% height);
    new Wolfberry(rand()% width, rand()% height);
    new Hogweed(rand()% width, rand()% height);
;
 
    new Guarana(rand()% width, rand()% height);
    new Wolfberry(rand()% width, rand()% height);
    new Guarana(rand()% width, rand()% height);
    new Wolfberry(rand()% width, rand()% height);
    new Guarana(rand()% width, rand()% height);
    new Wolfberry(rand()% width, rand()% height);
 
}
