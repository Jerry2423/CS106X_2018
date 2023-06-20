#include <iostream>
#include "console.h"
using namespace std;


struct ListNode {
    int data;         // element stored in each node
    ListNode* next;   // pointer to the next node (nullptr if none)

    ListNode(int d = 0, ListNode* n = nullptr) {
        data = d;
        next = n;
    }
};

void printList(ListNode *head) {
    ListNode *current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int mainFirst() {
    int x = 10;
    int *xPtr = &x;
    cout << xPtr << endl;
    *xPtr =20;
    cout << *xPtr << endl;
    int *nptr = nullptr;

    ListNode *head = new ListNode(42);
    head->next = new ListNode(17);
    head->next->next = new ListNode(-3);
    head->next->next->next = new ListNode(20);
    printList(head);

    head = head->next;

    printList(head);

    return 0;
}
