#include <iostream>
#include <string>
#include "set.h"
#include <cmath>
using namespace std;

int squareOfDigits(int a);
bool isHappyNumber(int a);

int main() {
    cout << isHappyNumber(127);
    return 0;
}

int squareOfDigits(int a) {
    int sum = 0;
    while (a != 0) {
        sum += pow(a%10, 2);
        a /= 10;
    }
    return sum;
}

bool isHappyNumber(int a) {
    Set<int> uniqueNums;
    int square = squareOfDigits(a);
    while (!uniqueNums.contains(square)) { //set去重，查询更快
        uniqueNums.add(square);
        square = squareOfDigits(square);
        if (square == 1)
            return true;
    }
    return false;
}
