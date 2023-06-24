#include "History.h"
#include "error.h"
using namespace std;

History::History() {
    /* TODO: Delete this line and implement this member function. */
    front_ = nullptr;
    curr_ = nullptr;
}

History::~History() {
    /* TODO: Delete this line and implement this member function. */
    delete_from(front_);
    front_ = nullptr; 
    curr_ = nullptr;
}

bool History::hasNext() const {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    if (empty()) {
        return false;
    }
    return curr_->next;
}

bool History::hasPrevious() const {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    if (empty()) {
        return false;
    }
    return curr_->prev;
}

string History::next() {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    if (!hasNext()) {
        error("no next page");
    } else {
        curr_ = curr_->next;
        return curr_->title;
    }
    return "";
}

string History::previous() {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    if (!hasPrevious()) {
        error("no previous page");
    } else {
        curr_ = curr_->prev;
        return curr_->title;
    }
    return "";
}

void History::goTo(const string& page) {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    // delete all the pages after the curr(if it has)
    if (hasNext()) {
        delete_from(curr_->next);
    } // if we do not set the curr->next = nullptr after deletion or in the delete function, curr->next will be a dangling ptr: memory leak! And infinite loop may occur
    //create new node
    add_back(page);
    // print();
    while (hasNext()) {
        curr_ = curr_->next;
    }
}

void History::delete_from(Node*& head) { // note the & after the *: need to be set to nullptr after releasing
    if (!head) {
        return;
    } else {
        delete_from(head->next);
        delete head;
        head = nullptr; // set the ptr to nullptr to avoid dangling ptr!
    }
}

void History::add_back(const string& title) {
    Node* temp = new Node {title, nullptr, nullptr};
    if (empty()) {
        front_ = temp;
        curr_ = temp;
    } else {
        Node* arrow = front_;
        while (arrow->next) {
            arrow = arrow->next;
        }
        temp->prev = arrow;
        arrow->next = temp;
    } 
}

bool History::empty() const {
    return !front_;
}

void History::print() const {
    if (!empty()) {
        auto arrow = front_;
        while (arrow) {
            cout << arrow->title << " ";
            arrow = arrow->next;
        }
        cout << endl;
    }
}
