#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
using namespace std;

void getName(string& name);
void upperDiamond(string name);
void lowerDiamond(string name);


int main()
{
    string name;
    getName(name);
    upperDiamond(name);
    lowerDiamond(name);
    return 0;
}

void getName(string &name) {
    cin >> name;
}

void upperDiamond(string name) {
    for (int i = 1; i <= name.length(); i++) {
        cout << name.substr(0, i) << endl; //s.substr(startIndex, length) length:整个字串（含起始位字符）的长度
    }
}

void lowerDiamond(string name) {
    for (int i = 1; i < name.length(); i++) {
        for (int j = 0; j < i; j++) cout << " ";
        cout << name.substr(i) << endl;
    }
}




/* * * * * * Test Cases * * * * * */

