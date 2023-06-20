#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;


/*Summary:
 * Use pointer to represent a list: ListNode* front;
 * Store pointer in stack; Store list in heap: new
 * When iterating a list: make a copy of front, i.e ListNode* current = front, use curr to iterate the list
 * For functions that change the list: use reference to pointer: ListPointer*& name;
 * Iterate over the list: while (curr) {} go all the way down
 * Operation over list: James Bond Analogy: curr goes to the node BEFORE the node of interest!
 *                      Consider special case when index = 0 since there is no carrage you Bond can stand on it.
 *                      Also consider: empty list
 * Remove element: clean up memory
 * Removal Mode: ListNode* trash = object;
 *               Operations;
 *               delete trash;
 */


struct ListNode {
    int data;         // element stored in each node
    ListNode* next;   // pointer to the next node (nullptr if none)

    ListNode(int d = 0, ListNode* n = nullptr) {
        data = d;
        next = n;
    }
};


// function prototype declarations
ListNode* vectorToLinkedList(const Vector<int>& v);
int size(ListNode* front);
int get(ListNode* front, int index);
void add(ListNode*& front, int value);
void addFirst(ListNode*& front, int value);
void insert(ListNode*& front, int index, int value);
void remove(ListNode*& front, int index);
void print(ListNode* front);
void clear(ListNode*& front);

int main() {
    Vector<int> v = {1, 2, 3, 4};
    ListNode* front = vectorToLinkedList(v);
    cout << size(front) << endl;
    print(front);
    cout << get(front, 0) << endl;

    add(front, 28);
    print(front);

    insert(front, 0, 88);
    print(front);

    remove(front, 0);
    print(front);

//    clear(front);
//    print(front);

    return 0;
}

ListNode* vectorToLinkedList(const Vector<int> &v) {
    if (v.size() == 0) {
        return nullptr;
    } else {
        ListNode* front = new ListNode(v[0]);
        ListNode* curr = front;
        for (int i = 1; i < v.size(); i++) {
            ListNode* newNode = new ListNode(v[i]);
            curr->next = newNode;
            curr = curr->next;
        }
        return front;
    }
}

void print(ListNode *front) {
    ListNode* curr = front;
    if (!front) {
        cout << "null" << endl;
    } else {
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
}

int size(ListNode *front) {
    int count = 0;
    while (front) {
        count += 1;
        front = front->next;
    }
    return count;
}

int get(ListNode* front, int index) {
    if (!front || index >= size(front) || index < 0) {
        throw "invalid input";
        return 0;
    }
    ListNode* curr = front;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

void add(ListNode*& front, int value) {
    if (!front) {
        front = new ListNode(value);
    } else {
        ListNode* curr = front;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new ListNode(value);
    }
}


void addFirst(ListNode *&front, int value) {
    ListNode* newNode = new ListNode(value);
    newNode->next = front;
    front = newNode;
}


void insert(ListNode *&front, int index, int value) {

    if (index == 0) {
        ListNode* newNode = new ListNode(value);
        newNode->next = front;
        front = newNode;

    } else {

        ListNode* curr = front;
        for (int i = 0; i < index-1; i++) {
            curr = curr->next;
        }
        ListNode* storePtr = curr->next;
        curr->next = new ListNode(value);
        curr->next->next = storePtr;
        /*
         * same but more simple:
         * ListNode* newNode = ListNode(value, curr->next);
         * curr->next = newNode;
         */
    }
}

void remove(ListNode*& front, int index) {
    if (!front || index < 0) {
        throw "invalid input";
    } else if (index == 0) {
        ListNode* trash = front;
        front = front->next;
        delete trash;
    }else  {
        ListNode* curr = front;
        for (int i = 0; i < index-1; i++) {
            curr = curr->next;
        }
        ListNode* trash = curr->next;
        curr->next = curr->next->next;
        delete trash;
    }
}

//void clear(ListNode*& front) {
//    ListNode* curr = front;

//    while (curr->next) {
//        ListNode* trash = curr;
//        curr = curr->next;
//        delete trash;
//    }
//}


