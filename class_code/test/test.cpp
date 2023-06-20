#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 5, b = 2, c = 8;
    swap(a, b);
    cout << a << " " << b << " " << c << endl;
    return 0;
}





/* * * * * * Test Cases * * * * * */

