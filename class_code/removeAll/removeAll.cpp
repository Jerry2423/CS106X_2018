#include <iostream>
#include <string>
#include "vector.h"
#include "console.h"
#include "SimpleTest.h"
using namespace std;

void removeAll(Vector<string> &vec, string s);

int main()
{
    Vector<string> s {"a", "b", "c", "b", "b", "d"};
    removeAll(s, "b");
    cout << s << endl;
    return 0;
}

void removeAll(Vector<string> &vec, string s) {
    //必须要倒着走，循环中改变vector指针i的移动方向要和vector slide方向一致
    for (int i = vec.size() - 1; i >= 0; i--){
        if (vec[i] == s) vec.remove(i);
    }
}


// a, c, d
// ^

/* * * * * * Test Cases * * * * * */

