#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

void printBinary(int n);

int mainBinary() {
    printBinary(7);
    return 0;
}

void printBinary(int n) {
    if  (n <= 1) {
        cout << n;
    } else {
        //recursive case n > 1
        //printBinary(42) = 101010
        //                  -----^ last digit = 42 % 2
        //other digits 10101:represent 42 / 2 = 21
        //someone can help me out with printBinarty(21); It's helpful so think someone smarter is helping you with the harder part.
        //all I have to do is print 42%2
        printBinary(n/2);
        cout << n % 2; // same: printBinary(42%2)
    }
}
