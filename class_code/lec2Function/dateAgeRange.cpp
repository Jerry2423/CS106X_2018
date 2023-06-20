#include <iostream>
#include <string>
#include <cmath>
#include "console.h"
#include "SimpleTest.h"
using namespace std;
//With prototype, only declare default values in prototype.
// set default value at last in prototype
void dateRange(int& low, int& high, int age = 18);
void getAge(int& age);
void printRange(int low, int high);

int main() {
    int age, low, high;
    getAge(age);
    dateRange(low, high);
    printRange(low, high);
    return 0;
}

void getAge(int& age) {
    cin >> age;
}

void dateRange(int& low, int& high, int age) {
    low = age / 2 + 7;
    high = (age - 7) * 2;
}

void printRange(int low, int high) {
    cout << low << "~" << high << endl;
}
