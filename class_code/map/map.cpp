#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include "map.h"
using namespace std;


int mainLearn()
{
    Map<string, int> phoneBook = {{"Jerry", 1186}, {"Marty", 759}}; //Map<KeyType, ValueType> map = {{ k1, v1}, { k2, v2 }};
    phoneBook["Tyler"] = 1175;
    phoneBook["John"] = 789;
    //phoneBook.remove("Jerry");
    for (string key: phoneBook.keys())
        cout << phoneBook[key] << endl;

    return 0;
}




/* * * * * * Test Cases * * * * * */

