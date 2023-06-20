#include <iostream>
#include <string>
#include "console.h"
using namespace std;

void permuteName(string name, string permute);

int mainPermute() {
    permuteName("MARTY", "");
    return 0;
}

void permuteName(string name, string permute) {
    static int count = 0;
    if (name.size() <= 1) {
        count += 1;
        cout <<count << " " << permute << name << endl;
    } else {
        for (int i = 0; i < name.size(); i++) {
            if (i < name.size()-1) {
                string before = name.substr(0, i);
                string after = name.substr(i+1, name.size()-1);
                permuteName(before+after, permute+name[i]);
            } else {
                permuteName(name.substr(0, i), permute+name[i]);
            }
        }
    }
}
