/*
 * CS 106X, Nick Troccoli
 * 
 * This program implements many linked list operations on chains
 * of ListNode objects.
 * Note that any method that modifies a linked list will pass the
 * 'front' pointer parameter by reference.
 * This is so that any changes to the front of the list propagate
 * back to the original list declared in main.
 */

#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

/*
 * The internal structure representing a single node of data.
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
void insert(ListNode*& front, int index, int value);
void remove(ListNode*& front, int index);
void print(ListNode* front);
void clear(ListNode*& front);

int main() {
    ListNode *front = vectorToLinkedList({42, -3, 17, 9});

    cout << "my list is: ";
    print(front);
    cout << "Size: " << size(front) << endl;

    cout << "Adding 12 to the back..." << endl;
    add(front, 12);
    print(front);
    cout << "Size: " << size(front) << endl;

    cout << "Inserting 81 at the front..." << endl;
    insert(front, 0, 81);
    print(front);
    cout << "Size: " << size(front) << endl;

    cout << "Adding 22 and 648 to the back..." << endl;
    add(front, 22);
    add(front, 648);
    print(front);
    cout << "Size: " << size(front) << endl;

    cout << "Removing front element..." << endl;
    remove(front, 0);
    print(front);
    cout << "Size: " << size(front) << endl;

    cout << "Removing index 2 element..." << endl;
    remove(front, 2);
    print(front);
    cout << "Size: " << size(front) << endl;

    cout << "Removing last element..." << endl;
    remove(front, size(front) - 1);
    print(front);
    cout << "Size: " << size(front) << endl;

    return 0;
}

/* Converts a vector to a linked list on the heap. */
ListNode *vectorToLinkedList(const Vector<int>& v) {
    if (v.size() == 0) return nullptr;
    ListNode *head = new ListNode(v[0], nullptr);
    ListNode *curr = head;
    for (int i = 1; i < v.size(); i++) {
        ListNode *node = new ListNode(v[i], nullptr);
        curr->next = node;
        curr = node;
    }
    return head;
}

// Returns the length of the list.
int size(ListNode* front) {
    ListNode* curr = front;
    int count = 0;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

/* Prints out the linked list starting at the given pointer.
 * Prints out the list on the same line with a space between each value.
 */
void print(ListNode* front) {
    if (front == nullptr) {
        cout << "(empty)" << endl;
    } else {
        ListNode* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}


// Returns value in list at given index.
// Assumes 0 <= index < size()
int get(ListNode* front, int index) {
    ListNode* curr = front;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

// Appends the given value to the end of the list.
void add(ListNode*& front, int value) {
    // create a new node
    ListNode* newNode = new ListNode(value);

    if (front == nullptr) {
        // empty list: store as new front of list
        front = newNode;
    } else {
        // non-empty list: walk to end of list
        ListNode* current = front;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Removes value at given index from list.
// I assume that 0 <= index < size.
void remove(ListNode*& front, int index) {
    if (index == 0) {
        // remove from front
        ListNode* nodeToDelete = front;
        front = front->next;
        delete nodeToDelete;
    } else {
        // non-front: walk to proper place in list
        ListNode* current = front;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        // remove the node
        ListNode* nodeToDelete = current->next;
        current->next = current->next->next;
        delete nodeToDelete;
    }
}

// Inserts the given value at the given index.
void insert(ListNode*& front, int index, int value) {
    if (index == 0) {
        // insert as front element
        front = new ListNode(value, front);
    } else {
        // non-front: walk to proper place in list
        ListNode* curr = front;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        
        // insert the node
        ListNode* newNode = new ListNode(value, curr->next);
        curr->next = newNode;
    }
}
