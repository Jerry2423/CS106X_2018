#include <iostream>
#include <string>
#include "gwindow.h"
#include <cmath>
using namespace std;

void cantorSet(GWindow& w, int x, int y, int length, int level);
void boxy(GWindow& w, int x, int y, int size, int level);
const double pi = 3.1415926;

int main() {
    GWindow window(800, 600);
    cantorSet(window, 50, 50, 700, 7);
    //window.drawPolygon([50, 50, 80, 80, 100, 100]);
    //window.drawPolarLine(50, 50, 80, 90);
    //boxy(window, 300, 300, 100, 4);
    return 0;
}

void cantorSet(GWindow &w, int x, int y, int length, int level) {
    if (level <= 1) {
        w.drawLine(x, y, x+length, y);
    } else {
        w.drawLine(x, y, x+length, y);
        cantorSet(w, x, y+20, length/3, level-1);
        cantorSet(w, x+length*2/3, y+20, length/3, level-1);
    }
}

void boxy(GWindow &w, int x, int y, int size, int level) {
    if (level <= 1) {
        w.fillRect(x, y, size, size);
    } else {
        //upper left
        boxy(w, x-size/2, y-size/2, size/2, level-1);
        // bottom right
        boxy(w, x+size/2, y+size/2, size/2, level-1);
        //center
        //w.fillRect(x, y, size, size);
        //bottom left
        boxy(w, x-size/2, y+size/2, size/2, level-1);
        //upper right
        boxy(w, x+size/2, y-size/2, size/2, level-1);
        w.fillRect(x, y, size, size);
    }
}
