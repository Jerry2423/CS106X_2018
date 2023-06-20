#include <iostream>
#include <string>
#include <fstream>
#include "console.h"
#include "recursion.h"
using namespace std;

void hanoiTower(int n);
void hanoiTowerHelper(int n, int start, int end);

int mainHanoi() {
    int n = 5;
    hanoiTower(3);
    return 0;
}

void hanoiTower(int n) {
    hanoiTowerHelper(n, 1, 2);
}

void hanoiTowerHelper(int n, int start, int end) {
    if (n <= 1) {
        cout << "from" << start << " to " << end << endl;
    } else {
        hanoiTowerHelper(n-1, 1, 3);
        hanoiTowerHelper(1, 1, 2);
        hanoiTowerHelper(n-1, 1, 2);
    }
}
