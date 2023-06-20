#include <iostream>
#include "console.h"
using namespace std;

void printAllBinary(int numDigits);

void printAllBinaryHelper(int numDigits, string soFar);

int mainBinary() {
    printAllBinary(3);
    return 0;
}

void printAllBinaryHelper(int numDigits, string soFar) {
    if (numDigits == 0) {
        cout << soFar << endl;
    } else {
        printAllBinaryHelper(numDigits-1, soFar+"0");
        printAllBinaryHelper(numDigits-1, soFar+"1");
    }
}

void printAllBinary(int numDigits) {
    printAllBinaryHelper(numDigits, "");
}
