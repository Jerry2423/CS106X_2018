#include <iostream>
#include "console.h"
#include "vector.h"
#include "linkedlist.h"
#include <string>
using namespace std;

void subSets(LinkedList<string>& v);
void subSetsHelper(LinkedList<string>& v, LinkedList<string>& chosen);

int main() {
    LinkedList<string> v = {"J", "B", "M", "S"};
    subSets(v);
    return 0;
}

void subSetsHelper(LinkedList<string> &v, LinkedList<string> &chosen) {
    if (v.isEmpty()) {
        cout << chosen << endl;
    } else {
        string s = v[0];
        v.remove(0);
        chosen.add(s);
        subSetsHelper(v, chosen);
        chosen.remove(chosen.size() - 1);
        subSetsHelper(v, chosen);
        v.insert(0, s);//undo
    }
}

void subSets(LinkedList<string> &v) {
    LinkedList<string> chosen;
    subSetsHelper(v, chosen);
}
