#include "listclass.h"
#include "listNode.h"

//ok

ListClass::ListClass()
{
    this->front = nullptr;
    this->currSize = 0;
}

ListClass::~ListClass() {
    clear(this->front);
    front = nullptr;
    this->toString();
    cout << "end!" << endl;
}


int ListClass::size() const {
    return this->currSize;
}


void ListClass::add(int data) {
    //cout << data << endl;
    ListNode<int>* newNode = new ListNode<int>(data, nullptr);
    if (front == nullptr) {
        this->front = newNode;
        //cout << "new node added" << newNode->data << endl;
        this->currSize += 1;
        return;
    }
    ListNode<int>* curr = this->front;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
    this->currSize += 1;
}


void ListClass::vectorToList(Vector<int>& v) {
    this->currSize += v.size();
    if (this->front == nullptr) {
        ListNode<int>* newNode = new ListNode(v[0]);
        this->front = newNode;
        ListNode<int>* curr = this->front;
        for (int i = 1; i < v.size(); i++) {
            ListNode<int>* newOne = new ListNode(v[i]);
            curr->next = newOne;
            curr = curr->next;
        }
    } else  {
        ListNode<int>* curr = this->front;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        for (int i = 0; i < v.size(); i++) {
            ListNode<int>* newOne = new ListNode(v[i]);
            curr->next = newOne;
            curr = curr->next;
        }
    }

}


//void clear();
//template<typename T>
int ListClass::get(int index) const {

    if (index < 0 || index >= this->currSize) {
        throw "invalid index";
    }

    ListNode<int>* curr = this->front;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}


void ListClass::insert(int index, int data) {
    ListNode<int>* curr = this->front;
    if (index < 0) {
        throw "invalid index";
    }
    if (index == 0) {
        ListNode<int>* newNode = new ListNode(data, this->front);
        this->front = newNode;
        this->currSize += 1;
        return;
    }
    for (int i = 0; i < index-1; i++) {
        curr = curr->next;
    }
    ListNode<int>* newNode = new ListNode(data, curr->next);
    curr->next = newNode;
    this->currSize += 1; //添加元素非常容易忘currSize
}


bool ListClass::isEmpty() const {
    return this->currSize == 0;
}


void ListClass::remove(int index) {
    if (index < 0 || index >= this->currSize) {
        throw "invalid index";
    }
    if (index == 0) {
        ListNode<int>* nodeToRemove = this->front;
        this->front = this->front->next;
        delete nodeToRemove;
        this->currSize -= 1;
        return;
    }

    ListNode<int>* curr = this->front;
    for (int i = 0; i < index-1; i++) {
        curr = curr->next;
    }

    ListNode<int>* nodeToRemove = curr->next;
    curr->next = curr->next->next;
    delete nodeToRemove;
    this->currSize -= 1;
}


void ListClass::toString() const {
    if (this->isEmpty()) {
        cout << "empty" << endl;
        return;
    }
    ListNode<int>* curr = this->front;
    //cout << this->currSize << endl;
    for (int i = 0; i < this->currSize; i++) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}


void ListClass::clear(ListNode<int>* front) {
    if (front == nullptr) {
        return;
    }
    clear(front->next);
    delete front;
    this->currSize -= 1;
}
