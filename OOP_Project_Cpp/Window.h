#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <stdlib.h>

class Window {
public:
    Window(int width, int height, int x, int y);
    ~Window();

    void startGame();
    void initWindow();
    void cleanup();
    void starterScreen();
    void gameOverScreen();

    WINDOW* getWindow() const;

private:
    int width;
    int height;
    int x;
    int y;
    WINDOW* window;
};

#endif // WINDOW_H