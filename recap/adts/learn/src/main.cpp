#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include "set.h"
#include "vector.h"
#include "console.h"
using std::cout;
using std::endl;

int main() {
    cout << "hi" << endl;
    Set<Vector<int>> stanford_set {{1, 2, 3}, {1, 2}};
    
    for (auto& i : stanford_set) {
        if (i.size() < 3) {
            i.push_back(3);
        }
    }
    cout << stanford_set << endl;

    std::set<std::vector<int>> std_set {{1, 2, 3}, {1, 2}};
    for (auto& i : std_set) {
        if (i.size() < 3) {
            std::vector<int> temp = i;
            temp.push_back(3);
            std_set.erase(i);
            std_set.insert(temp);
        }
    }

    for (auto& i : std_set) {
        for (int j = 0; j < i.size(); j++) {
            cout << i[j] << " ";
        }
        cout << endl;

    }

    return 0;
}
