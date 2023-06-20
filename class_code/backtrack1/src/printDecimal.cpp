#include <iostream>
#include "console.h"
using namespace std;

void printAllDecimal(int numDigits, string soFar = "");

int mainDecimal() {

    printAllDecimal(2);

    return 0;
}

void printAllDecimal(int numDigits, string soFar) {
    if (numDigits == 0) {
        cout << soFar << endl;
    } else {
        string nums = "0123456789";
        for (char c: nums) {
            printAllDecimal(numDigits-1, soFar+c);
        }
    }
}
