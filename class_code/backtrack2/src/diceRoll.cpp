#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

void diceRollHelper(int dice, Vector<int>& rolls);

void diceRoll(int dice);


int mainRoll() {
    diceRoll(2);
    return 0;
}

void diceRollHelper(int dice, Vector<int> &rolls) {
    if (dice == 0) {
        cout << "{";
        for (int i = 0; i < rolls.size(); i++) {
            cout << rolls[i];
            if (i < rolls.size() - 1)
                cout << ", ";
        }
        cout << "}" << endl;
    } else {
        for (int i = 1; i <= 6; i++) {
            rolls.add(i);
            diceRollHelper(dice-1, rolls);
            //new things undo the choice: pass by reference undo
            rolls.remove(rolls.size()-1);
        }
    }
}

void diceRoll(int dice) {
    Vector<int> v;
    diceRollHelper(dice, v);
}
