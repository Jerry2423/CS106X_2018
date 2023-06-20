#include <iostream>
#include <string>
#include "console.h"
#include "SimpleTest.h"
#include "queue.h"
using namespace std;


/*queue:FIFO
 * Elements are stored in order of insertion but don't have indexes.
 * Can add only to the end of the queue, and can only examine/remove the front.
 * enqueue: Add an element to the back.
 * dequeue: Remove the front element.
 * peek: Examine the front element.
*/
int main()
{
    Queue<int> q;
    q.enqueue(1); //front -> back
    q.enqueue(42);
    q.enqueue(3);
    q.enqueue(4);//{1, 42, 3, 4}
    cout << q.dequeue() << endl;
    cout << q.peek() << endl;

    /*queue idioms:
     * As with stacks, must pull contents out of queue to view them.
     * another idiom: Examining each element exactly once.
    */

    while (!q.isEmpty()) {
        //do something with q.dequeue();
        //q.dequeue()
    }

    int qSize = q.size();
    for (int i = 0: i < qSize; i++) {
        /*
         * do something with q.dequeue();
         * (including possibly re-adding it to the queue)
        */
        //a = q.dequeue()
        //q.enqueue(a)
    }
    //Note: we must store the size of queue in the qSize, only by doing so can we iterate each element exactly once/
    //If we use i < q.size() directly, q.size() is changing, so we can't iterate over each element.

    return 0;
}




/* * * * * * Test Cases * * * * * */

