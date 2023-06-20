#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

void diceSum(int dice, int disiredSum);
void diceSumHelper(int dice, int disiredSum, int mysumSoFar, Vector<int>& chosen);
//int allSum(Vector<int> v);

int mainSum() {
    diceSum(2, 7);
    return 0;
}

//int allSum(Vector<int> v) {
//    int sum = 0;
//    for (int i : v)
//        sum += i;
//    return sum;
//}

void diceSumHelper(int dice, int disiredSum, int mysumSoFar, Vector<int> &chosen) {
    if (dice == 0) {
        if (mysumSoFar == disiredSum) {
            cout << chosen << endl;
        }
    } else {
        for (int i = 1; i <= 6; i++) {
            int min = mysumSoFar + 1*(dice-1) + i;
            int max = mysumSoFar + 6*(dice-1) + i;
            //prune the tree.假设选了，后面会怎么样？
            if (disiredSum >= min && disiredSum <= max) {
                chosen.add(i);
                diceSumHelper(dice-1, disiredSum, mysumSoFar+i, chosen);
                chosen.remove(chosen.size()-1);
            }
        }
    }
}

void diceSum(int dice, int disiredSum) {
    Vector<int> v;
    diceSumHelper(dice, disiredSum, 0, v);
}
