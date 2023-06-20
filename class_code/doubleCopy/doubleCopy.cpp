#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include "queue.h"
using namespace std;

Queue<int> doubleCopy(Queue<int>& q);

int main()
{
    Queue<int> q = {1, 2, 3};
    cout << doubleCopy(q) << endl;
    return 0;
}

Queue<int> doubleCopy(Queue<int> &q) {
    Queue<int> copyDouble;
    while (!q.isEmpty()) {
        int element = q.dequeue();
        copyDouble.enqueue(element);
        copyDouble.enqueue(element);
    }
    return copyDouble;
}



/* * * * * * Test Cases * * * * * */

