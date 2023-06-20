#include "listclass.h"
#include "listNode.h"

//ok
template<typename T>
ListClass<T>::ListClass()
{
    front = nullptr;
    currSize = 0;
}

template<typename T>
ListClass<T>::~ListClass() {
    clear(this->front);
    front = nullptr;
    this->toString();
    cout << "end!" << endl;
}

template<typename T>
int ListClass<T>::size() const {
    return this->currSize;
}

template<typename T>
void ListClass<T>::add(T data) {
    //cout << data << endl;
    ListNode<T>* newNode = new ListNode<T>(data, nullptr);
    if (front == nullptr) {
        this->front = newNode;
        //cout << "new node added" << newNode->data << endl;
        this->currSize += 1;
        return;
    }
    ListNode<T>* curr = this->front;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
    this->currSize += 1;
}

template<typename T>
void ListClass<T>::vectorToList(Vector<T>& v) {
    this->currSize += v.size();
    if (this->front == nullptr) {
        ListNode<T>* newNode = new ListNode(v[0]);
        this->front = newNode;
        ListNode<T>* curr = this->front;
        for (int i = 1; i < v.size(); i++) {
            ListNode<T>* newOne = new ListNode(v[i]);
            curr->next = newOne;
            curr = curr->next;
        }
    } else  {
        ListNode<T>* curr = this->front;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        for (int i = 0; i < v.size(); i++) {
            ListNode<T>* newOne = new ListNode(v[i]);
            curr->next = newOne;
            curr = curr->next;
        }
    }

}


//void clear();
template<typename T>
T ListClass<T>::get(int index) const {

    if (index < 0 || index >= this->currSize) {
        throw "invalid index";
    }

    ListNode<T>* curr = this->front;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

template<typename T>
void ListClass<T>::insert(int index, T data) {
    ListNode<T>* curr = this->front;
    if (index < 0) {
        throw "invalid index";
    }
    if (index == 0) {
        ListNode<T>* newNode = new ListNode(data, this->front);
        this->front = newNode;
        this->currSize += 1;
        return;
    }
    for (int i = 0; i < index-1; i++) {
        curr = curr->next;
    }
    ListNode<T>* newNode = new ListNode(data, curr->next);
    curr->next = newNode;
    this->currSize += 1; //添加元素非常容易忘currSize
}

template<typename T>
bool ListClass<T>::isEmpty() const {
    return this->currSize == 0;
}

template<typename T>
void ListClass<T>::remove(int index) {
    if (index < 0 || index >= this->currSize) {
        throw "invalid index";
    }
    if (index == 0) {
        ListNode<T>* nodeToRemove = this->front;
        this->front = this->front->next;
        delete nodeToRemove;
        this->currSize -= 1;
        return;
    }

    ListNode<T>* curr = this->front;
    for (int i = 0; i < index-1; i++) {
        curr = curr->next;
    }

    ListNode<T>* nodeToRemove = curr->next;
    curr->next = curr->next->next;
    delete nodeToRemove;
    this->currSize -= 1;
}

template<typename T>
void ListClass<T>::toString() const {
    if (this->isEmpty()) {
        cout << "empty" << endl;
        return;
    }
    ListNode<T>* curr = this->front;
    //cout << this->currSize << endl;
    for (int i = 0; i < this->currSize; i++) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

template<typename T>
void ListClass<T>::clear(ListNode<T>* front) {
    if (front == nullptr) {
        return;
    }
    clear(front->next);
    delete front;
    this->currSize -= 1;
}

/*
template<typename T>
ostream& operator <<(ostream& out, const ListClass<T>& list) {
    if (list.isEmpty()) {
        out << "empty";
        return out;
    }
    if (list.currSize == 1) {
        out << list.front->data;
        return out;
    }
    ListNode<T>* curr = list.front;
    for (int i = 1; i < list.currSize-1; i++) {
        out << curr->data << " <- ";
        curr = curr->next;
    }
    out << curr->next->data;
    return out;
}
*/

