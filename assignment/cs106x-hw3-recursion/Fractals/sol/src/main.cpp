#include "fractalgui.h"


int main() {
    FractalGUI gui;
    gui.initialize();
    gui.eventLoop();
    return 0;
}
