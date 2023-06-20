/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "listclass.h"
//using namespace std;


int main()
{
    ListClass myList{};
    Vector<int> v = {1, 2, 3, 4};
    myList.add(9);
    myList.vectorToList(v);
    cout << "execute" << endl;
    myList.toString();
    cout << myList.size() << endl;
    //cout << myList.get(-1) << endl;
    myList.insert(4, 900);
    myList.toString();
    myList.remove(3);
    myList.toString();
    //cout << myList << endl;

//    ListClass<string> mySList{};
//    Vector<string> s = {"hi", "hello", "nihao"};
//    mySList.vectorToList(s);
//    mySList.toString();
    return 0;
}
