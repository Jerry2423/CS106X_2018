#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include "queue.h"
#include "stack.h"
using namespace std;

void mirror(Queue<string> &q) {
    Stack<string> oppositeOrder;
    int qSize = q.size();
    for (int i = 0; i < qSize; i++) {
        string s = q.dequeue();
        oppositeOrder.push(s);
        q.enqueue(s);
    }

    while (!oppositeOrder.isEmpty()) {
        q.enqueue(oppositeOrder.pop());
    }
}

int main()
{
   Queue<string> q = {"a", "b", "c"};
   mirror(q);
   cout << q << endl;
   return 0;
}




/* * * * * * Test Cases * * * * * */

