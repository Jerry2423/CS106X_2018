/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "arraystack.h"
using namespace std;


int main()
{
    ArrayStack myStack{};
    myStack.push(1);
    cout << myStack << endl;
    myStack.push(2);
    cout << myStack << endl;
    myStack.push(3);
    cout << myStack << endl;
    myStack.push(10);
    cout << myStack << endl;
    cout << "execute" << endl;

    cout << myStack.pop() << endl;
    cout << myStack << endl;
    cout << myStack.pop() << endl;
    cout << myStack << endl;
    cout << myStack.pop() << endl;
    cout << myStack << endl;
    cout << myStack.pop() << endl;
    cout << myStack << endl;
    return 0;
}
