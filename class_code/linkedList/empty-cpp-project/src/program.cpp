#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

struct ListNode
{
    int d;
    ListNode* next;
    ListNode(int data = 0, ListNode* next = nullptr) {
        d = data;
        next = next;
    }
};

ListNode* vectorToLinkedList(const Vector<int>& v);
int size(ListNode* front);
int get(ListNode* front, int index);
void add(ListNode** front, int value);
void insert(ListNode*& front, int index, int value);
void remove(ListNode*& front, int index);
void print(ListNode* front);
void clear(ListNode*& front);

int main() {
    Vector<int> v = {1, 2, 3, 4};
    ListNode* head = vectorToLinkedList(v);
    print(head);
    cout << get(head, 2) << endl;
    add(&head, 10);
    print(head);
    remove(head, 2);
    print(head);
    insert(head, 2, 7);
    print(head);
    //cout << "Hello, world!" << endl;
    return 0;
}

void print(ListNode* front) {
    ListNode* curr = front;

    while(curr != nullptr) {
        cout << curr->d << " ";
        curr = curr->next;
    }
    cout << endl;
}

ListNode* vectorToLinkedList(const Vector<int>& v) {
    if (v.size() <= 0) {
        return nullptr;
    }
    ListNode* head = new ListNode(v[0], nullptr);
    ListNode* curr = head;

    for (int i = 0; i < v.size(); i++) {
        ListNode* newNode = new ListNode(v[i], nullptr);
        curr->next = newNode;
        curr = curr->next;
    }

    return head;

}

int size(ListNode* front) {
    int k = 0;
    ListNode* curr = front;
    while (curr != nullptr) {
        k += 1;
        curr = curr->next;
    }
    return k;
}

int get(ListNode* front, int index) {
    if (index >= size(front)) {
        return -1;
    }
    ListNode* curr = front;

    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    return curr->d;

}

void add(ListNode** front, int value) {
    ListNode* newNode = new ListNode(value, nullptr);
    if (*front == nullptr) {
        *front = newNode;
        return;
    }

    ListNode* curr = *front;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;

}

//void remove(ListNode*& front, int index) {
//    if (index == 0) {
//        ListNode* nodeToDelete = front;
//        front->next = front->next->next;
//        delete nodeToDelete;
//        return;
//    }

//    ListNode* curr = front;
//    for (int i = 0; i < index-1; i++) {
//        curr = curr->next;
//    }
//    ListNode* nodeToDelete = curr->next;
//    curr->next = curr->next->next;
//    delete nodeToDelete;
//}

void insert(ListNode*& front, int index, int value) {
    if (index == 0) {
        ListNode* newNode = new ListNode(value, front);
        front = newNode;
        return;
    }

    ListNode* curr = front;
    for (int i = 0; i < index-1; i++) {
        curr = curr->next;
    }
    ListNode* newNode = new ListNode(value, curr->next);
    curr->next = newNode;
}


void remove(ListNode*& front, int index) {

    if (index == 0) {
        ListNode* nodeToRemove = front;
        front->next = front->next->next;
        delete nodeToRemove;
        return;
    }

    ListNode* curr = front;
    for (int i = 0; i < index-1; i++) {
        curr = curr->next;
    }
    ListNode* nodeToRemove = curr->next;
    curr->next = curr->next->next;
    delete nodeToRemove;

}
