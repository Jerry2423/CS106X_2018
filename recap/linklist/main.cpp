#include <iostream>
#include <iterator>
#include "linklist.h"
//std:next,advance
using std::cout;
using std::endl;

int main() {
    MyLinkList fun {1, 2, 3, 4};
    MyLinkList foo = fun;
    cout << fun << endl;
    cout << foo << endl;
    fun.pop_front();
    cout << fun << endl;
    cout << fun.size() << endl;
    fun.push_front(99);
    fun.push_front(66);
    cout << fun << endl;
    cout << fun.size() << endl; // 66,99,1,2,3,4
    fun.insert_after(std::next(fun.begin(), 2), 77);
    cout << fun << endl;
    cout << fun.size() << endl;
    // if (memcheck::all_deallocated()) {
    //     cout << "great!" << endl;
    // } else {
    //     cout << "memory leak" << endl;
    // }
    fun.erase_after(std::next(fun.begin(), 3));
    cout << fun << endl;
    cout << fun.size() << endl;
    // fun.pop_front();
    // fun.pop_front();
    // fun.pop_front();
    // fun.pop_front();
    // fun.erase_after(fun.begin());
    // cout << fun << endl;
    fun.reverse();
    fun.add_back(48);
    cout << fun << endl;
    fun.remove(1);
    cout << fun << endl;
    cout << fun[3] << endl;
    fun[3] = 35;
    fun.reverse();
    cout << fun << endl;
    MyLinkList edge;
    // edge.insert_after(edge.begin(), 9); //undefined behavior
    // cout << edge << endl;
    return 0;
}
