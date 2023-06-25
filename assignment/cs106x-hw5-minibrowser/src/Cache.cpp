#define CacheCPP_Included
#include "Cache.h"
using namespace std;

//TODO hashmap add and removal
template <typename ValueType>
Cache<ValueType>::Cache(int maxSize) : maxSize(maxSize), front(nullptr), end(nullptr), currSize(0){
    /* TODO: Delete this line, delete the next line, and implement this member function. */
}

template <typename ValueType>
Cache<ValueType>::~Cache() {
    /* TODO: Delete this line and implement this function. */
    delete_from(front);
    for (const auto& i : info) {
        info[i] = nullptr;
    }
    end = nullptr;
    currSize = 0;
}

template <typename ValueType>
void Cache<ValueType>::put(const std::string& key, const ValueType& value) {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    if (info.containsKey(key)) {
        move_end(info[key]);
    } else {
        if (currSize == maxSize) {
            pop_front();
        }
        push_back(key, value);
    }
}

template <typename ValueType>
bool Cache<ValueType>::containsKey(const std::string& key) const {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    (void) key;
    return info.containsKey(key);
}

template <typename ValueType>
ValueType Cache<ValueType>::get(const std::string& key) {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    if (info.containsKey(key)) {
        move_end(info[key]);
        return info[key]->value;
    } else {
        error("invalid key");
    }
    return {};
}

template<typename ValueType>
void Cache<ValueType>::delete_from(Node*& curr) {
    if (!curr) {
        return;
    } else {
        delete_from(curr->next);
        info.remove(curr->key);
        delete curr;
        curr = nullptr;
        currSize--;
    }
}

template<typename ValueType>
bool Cache<ValueType>::empty() const {
    return !front;
}

template<typename ValueType>
void Cache<ValueType>::pop_front() {
    if (!empty()) {
        Node* temp = front;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        }
        info.remove(temp->key);
        delete temp;
        currSize--;
        if (empty()) {
            end = nullptr;
        }
    }
}

template<typename ValueType>
void Cache<ValueType>::push_back(const string& key, const ValueType& value) {
    Node* temp = new Node {key, value, end, nullptr};
    info[key] = temp;
    if (!empty()) {
        end->next = temp;
    } else {
        front = temp;
    }
    end = temp;
    currSize++;
}

template<typename ValueType>
void Cache<ValueType>::move_end(Node* ptr) {
    if (empty() || ptr == end) {
        return;
    } else if (ptr == front) {
        Node* temp = front;
        front = front->next;
        front->prev = nullptr;
        temp->next = nullptr;
        temp->prev = end;
        end->next = temp;
        end = temp;
    } else {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        ptr->next = nullptr;
        ptr->prev = end;
        end->next = ptr;
        end = ptr;
    }
}
