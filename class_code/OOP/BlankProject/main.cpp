/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "bankaccount.h"
using namespace std;


template<typename T>
T myMax(T a, T b) {
    if (a >= b) {
        return a;
    } else  {
        return b;
    }
}


int main()
{
    BankAccount marty("Marty", 100);
    cout << marty.getName() << endl;

    BankAccount martyCopy("Marty", 100);
    if (marty == martyCopy) {
        cout << 1 << endl;
    }

    cout << marty << endl;

    int i = myMax(1, 2);
    double j = myMax(17.5, 1.9);
    cout << i <<" " << j << endl;

    return 0;
}
