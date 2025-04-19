#include "Window.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

Window::Window(int width, int height, int x, int y)
    : width(width), height(height), x(x), y(y), window(nullptr) {}

Window::~Window() {
    cleanup();
}

void Window::startGame() {
    if ((window = initscr()) == nullptr) {
        fprintf(stderr, "Ncurses could not be initialized.\n");
        exit(EXIT_FAILURE);
    }
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
    }
    curs_set(0);
    noecho();
}

void Window::initWindow() {
    window = newwin(height, width, y, x);
    if (!window) {
        fprintf(stderr, "Failed to create window.\n");
        exit(EXIT_FAILURE);
    }
    box(window, 0, 0);
    wrefresh(window);
}

void Window::cleanup() {
    if (window) {
        delwin(window);
        window = nullptr;
    }
    endwin();
}
void Window::starterScreen() {
    if (!window) {
        fprintf(stderr, "Window not initialized.\n");
        return;
    }

    int newWidth = width; 
    int newHeight = height; 

    wclear(window);
    mvwaddstr(window, 1, 1, "Simulation Game");
    mvwaddstr(window, 2, 1, "Rules:");
    mvwaddstr(window, 3, 1, "- WASD to move");
    mvwaddstr(window, 4, 1, "- P to quit ");
    mvwaddstr(window, 5, 1, "- N for new game ");
    
    mvwaddstr(window, 7, 1, "Choose map size:");

    mvwprintw(window, 8, 1, "Enter width (5-50): ");
    wrefresh(window);
    echo(); 
    wscanw(window, "%d", &newWidth); 

    mvwprintw(window, 9, 1, "Enter height (5-50): ");
    wrefresh(window);
    wscanw(window, "%d", &newHeight); 
    noecho(); 
    if (newWidth < 5 || newWidth > 50) {
        newWidth = width;
    }
    if (newHeight < 5 || newHeight > 50) {
        newHeight = height; 
    }
    width = newWidth;
    height = newHeight;

    mvwaddstr(window, 11, 1, "Press any key to start...");
    wrefresh(window);
    wgetch(window); 
    wclear(window);
    wrefresh(window);
}

WINDOW* Window::getWindow() const {
    return window;
}