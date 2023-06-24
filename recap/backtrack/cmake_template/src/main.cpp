#include <iostream>
#include "collections/vector.h"
#include <graphics/gwindow.h>
#include <io/tokenscanner.h>
#include <io/console.h>
#include <collections/set.h>
using namespace std;

void permute(const string& s, string record) {
    if (s.empty()) {
        cout << record << endl;
    } else {
        //go through each choice
        for (int i = 0; i < s.size(); i++) {
            //choose one and explore
            //make a copy for s so that s is preserved for the following decisions
            string temp = s;
            temp.erase(i,1);
            permute(temp, record+s[i]);
        }
    }
}

void diceRollHelper(int dice, Vector<int>& chosen) {
    if (dice == 0) {
        cout << chosen << endl;
    } else {
        for (int i = 1; i <= 6; i++) {
            chosen.add(i);
            diceRollHelper(dice-1, chosen);
            chosen.remove(chosen.size()-1);
        }
    }
}

void diceRole(int dice) {
    Vector<int> chosen;
    diceRollHelper(dice, chosen);
}

void diceSumHelper(int dice, int curr_sum, Vector<int>& chosen) {
    if (dice == 0) {
        if (curr_sum == 0) {
            cout << chosen << endl;
        }
        return;
    } else {
        for (int i = 1; i <= 6; i++) {
            int min = (dice-1) * 1;
            int max = (dice-1) * 6;
            //prune
            if (curr_sum-i >= min && curr_sum-i <= max) {
                chosen.add(i);
                diceSumHelper(dice-1, curr_sum-i, chosen);
                chosen.remove(chosen.size()-1);
            }
        }
    }
}

void diceSum(int dice, int desired_sum) {
    Vector<int> chosen;
    diceSumHelper(dice, desired_sum, chosen);
}

void sublistsHelper(Vector<string>& v, Vector<string>& chosen) {
    if (v.isEmpty()) {
        cout << chosen << endl;
    } else {
        string s = v[v.size()-1];
        v.remove(v.size()-1);
        chosen.add(s);
        sublistsHelper(v, chosen);
        chosen.remove(chosen.size()-1);

        sublistsHelper(v, chosen);
        v.add(s);
    }
}

void sublists(Vector<string>& v) {
    Vector<string> chosen;
    sublistsHelper(v, chosen);
}

int main() {
    // permute("marty", "");
    // diceRole(2);
    // diceSum(3, 11);
    Vector<string> names {"jane", "bob", "matt", "sara"};
    sublists(names);
    return 0;
}
