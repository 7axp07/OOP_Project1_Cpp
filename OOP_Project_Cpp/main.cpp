#include <iostream>
#include "Window.h"
using namespace std;

int main() {
    Window mainWindow(80, 24, 0, 0);
    mainWindow.startGame();
    mainWindow.initWindow();
    mainWindow.starterScreen();
    mainWindow.cleanup();
    return EXIT_SUCCESS;
}