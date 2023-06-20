
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "set.h"

using namespace std;

void printAllBinary(int numDigits);
void printAllBinaryHelper(int digits, string soFar);
void diceRolls(int dice);
void diceRollHelper(int dice, Vector<int> &chosen);
void diceSum(int dice, int desiredSum);
void diceSumHelper(int dice, int sum, int desiredSum, Vector<int> &chosen, int minDieValue);
void subSets(const Set<string> &masterSet);
void listSubsetsRec(const Set<string> &masterSet, const Set<string> &used);

int main() {
    printAllBinary(3);
    cout << "---" << endl;
    diceRolls(3);
    cout << "---" << endl;
    diceSum(3, 7);
    cout << "---" << endl;
    subSets({"Nick", "Greeshma", "Avi", "Christina", "David"});
    return 0;
}

/** BINARY PRINTING **/

void printAllBinary(int numDigits) {
    printAllBinaryHelper(numDigits, "");
}

void printAllBinaryHelper(int digits, string soFar) {
    if (digits == 0) {
        cout << soFar << endl;
    } else {
        printAllBinaryHelper(digits - 1, soFar + "0");
        printAllBinaryHelper(digits - 1, soFar + "1");
    }
}

/** DICE ROLLS **/

// Prints all possible outcomes of rolling the given
// number of six-sided dice in {#, #, #} format.
void diceRolls(int dice) {
    Vector<int> chosen;
    diceRollHelper(dice, chosen);
}

// private recursive helper to implement diceRolls logic
void diceRollHelper(int dice, Vector<int>& chosen) {
    if (dice == 0) {
        cout << chosen << endl;                 // base case
    } else {
        for (int i = 1; i <= 6; i++) {
            chosen.add(i);                      // choose
            diceRollHelper(dice - 1, chosen);   // explore
            chosen.remove(chosen.size() - 1);   // un-choose
        }
    }
}

/** UNIQUE DICE SUMS **/

void diceSum(int dice, int desiredSum) {
    Vector<int> chosen;
    diceSumHelper(dice, 0, desiredSum, chosen, 1);
}

void diceSumHelper(int dice, int sum, int desiredSum, Vector<int>& chosen,
    int minDieValue) {
    if (dice == 0) {
        if (sum == desiredSum) {
            cout << chosen << endl;                            // base case
        }
    } else if (sum + 1*dice <= desiredSum
            && sum + 6*dice >= desiredSum) {
        for (int i = minDieValue; i <= 6; i++) {
            chosen.add(i);                                        // choose
            diceSumHelper(dice - 1, sum + i, desiredSum, chosen, i);//explore
            chosen.remove(chosen.size() - 1);                  // un-choose
        }
    }
}

/** SUBSETS **/

void subSets(const Set<string>& masterSet) {
    Set<string> chosen;
    listSubsetsRec(masterSet, chosen);
}

void listSubsetsRec(const Set<string>& masterSet, const Set<string>& used) {
    if (masterSet.isEmpty()) {
        cout << used << endl;
    } else {
        string element = masterSet.first();

        listSubsetsRec(masterSet - element, used);           // Without
        listSubsetsRec(masterSet - element, used + element); // With
    }
}



