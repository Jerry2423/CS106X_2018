#ifndef LINKLIST_H__
#define LINKLIST_H__


#include <iostream>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <memory>

struct ListNode {
    int data;
    ListNode* next;
};

//TODO: template, < operator, const correctness.

class MyLinkList {
    public:
        using data_type = int;
        using size_type = size_t;
        using reference = data_type&;
        using const_reference = const data_type&;
        // using iterator = ListNode*;
        // using const_iterator = const ListNode*;
        
        //default constructor
        MyLinkList() : front_(nullptr), length_(0) {}
        //destrctor
        ~MyLinkList() {
            clean();
        } 
        //copy constructor
        MyLinkList(const MyLinkList& other) : length_(other.size()) {
            if (other.size() > 0) {
                ListNode* curr = other.front_;
                front_ = new ListNode {curr->data, nullptr};
                ListNode* temp = front_;
                curr = curr->next;
                while (curr != nullptr) {
                    //create newnode
                    //set temp->next = new node
                    temp->next = new ListNode {curr->data, nullptr};
                    //move temp and curr to the next
                    temp = temp->next;
                    curr = curr->next;
                }
            } else {
                front_ = nullptr;
            }
        }
        //copy assignment
        void swap(MyLinkList& other) {
            std::swap(other.front_, front_);
            std::swap(other.length_, length_);
        }
        MyLinkList& operator=(MyLinkList other) {
            swap(other);
            return *this;
        }
        //move constructor
        MyLinkList(MyLinkList&& other) : length_(other.length_), front_(other.front_) {
            other.length_ = 0;
            other.front_ = nullptr;
        }
        //move assignment
        //copy and swap + swap
        //initializer_list constructor
        MyLinkList(std::initializer_list<data_type> init) : length_(init.size()) {
            if (init.size() > 0) {
                front_ = new ListNode {*init.begin(), nullptr};
                ListNode* temp = front_;
                for (auto i = init.begin()+1; i != init.end(); ++i) {
                    temp->next = new ListNode {*i, nullptr};
                    temp = temp->next;
                }
            } else {
                front_ = nullptr;
            }
        }

        //push_front_
        void push_front(const data_type& value) {
            if (empty()) {
                front_ = new ListNode{value, nullptr};
                length_ += 1;
            } else {
                ListNode* temp = new ListNode{value, front_};
                front_ = temp;
                length_ += 1;
            }
        }
        //pop_front
        void pop_front() {
            if (!empty()) {
                ListNode* temp = front_;
                front_ = front_->next;
                delete temp;
                length_ -= 1;
            }
        }
        
        void reverse() {
            if (!empty()) {
                front_ = reverseHelper(front_, nullptr);
            }
        }

        friend class iterator;

        class iterator : public std::iterator<std::forward_iterator_tag, data_type> {
            public:
                friend MyLinkList;
                //copy constructor public?
                iterator(const iterator& it) : pointee_(it.pointee_) {}
                //copy assignment public?
                iterator& operator =(const iterator& it) {
                    if (it.pointee_ != pointee_) {
                        delete pointee_;
                        pointee_ = it.pointee_;
                    }
                    return *this;
                }
                //destructor: default
                ~iterator() = default;
                //non-member: == and !=

                //base
                ListNode* base() const {
                    return pointee_;
                }
                //next
                ListNode* next() const {
                    return pointee_->next;
                }
                //++ operator(posfix and prefix) member
                iterator& operator++() {
                    pointee_ = pointee_->next;
                    return *this;
                }
                iterator operator++(int) {
                    auto temp = *this;
                    pointee_ = pointee_->next;
                    return temp;
                }
                //*operator
                reference operator*() {
                    return pointee_->data;
                }
                const_reference operator*() const {
                    return pointee_->data;
                }
                //->iterator
                auto operator->() {
                    return std::addressof(operator*());
                }
                const auto operator->() const {
                    return std::addressof(operator*());
                }
                
            private:
                //constructor: it(ListNode* pointee): private: only friend can construc
                iterator(ListNode* pointee) : pointee_(pointee) {};
                ListNode* pointee_;
        };
        //insert_after
        iterator insert_after(iterator it, const data_type& value) {
           auto temp = it.pointee_->next;
           it.pointee_->next = new ListNode{value, temp};
           length_ += 1;
           return iterator(it.base()->next);
        }
        //erase_after
        //undefined behavior: it is the end.
        void erase_after(iterator it) {
            if (it.base()->next) {
                auto temp = it.pointee_->next;
                it.pointee_->next = it.pointee_->next->next;
                delete temp;
                length_ -= 1;
            }
        }

        void add_back(const data_type& value) {
            if (empty()) {
                front_ = new ListNode {value, nullptr};
            } else {
                insert_after(std::next(begin(), size()-1), value);
            }
        }
        void remove(size_type index) {
            if (!empty()) {
                if (index == 0) {
                    pop_front();
                } else {
                    erase_after(std::next(begin(), index-1));
                }
            }
        }

        reference operator[](size_type index) {
            return *std::next(begin(), index);
        }

        const_reference operator[](size_type index) const {
            return *std::next(begin(), index);
        }

        //size
        int size() const {
            return length_;
        }
        //empty
        bool empty() const {
            return length_ == 0;
        }
        //clean
        void clean() {
            if (!empty()) {
                auto temp = front_->next;
                while (temp) {
                    delete front_;
                    front_ = temp;
                    temp = temp->next;
                }
                delete front_;
            }
            length_ = 0;

        }
        //iterator:begin+end
        iterator begin() {
            return iterator(front_);
        }
        iterator end() {
            return iterator(nullptr);
        }
        const iterator begin() const {
            return iterator(front_);
        }
        const iterator end() const {
            return iterator(nullptr);
        }


    private:
        static void deleteFrom(ListNode* head) {
            if (!head) {
                return;
            } else {
                deleteFrom(head->next);
                delete head;
            }
        }

        ListNode* reverseHelper(ListNode* curr, ListNode* prev) {
            if (!curr->next) {
                curr -> next = prev;
                return curr;
            }
            // ListNode* new_head = reverseHelper(curr->next, curr);
            // curr->next = prev;
            // return new_head;
            //better tail recursion way
            auto temp = curr->next;
            curr->next = prev;
            return reverseHelper(temp, curr);
        }

        ListNode* front_;
        size_type length_;
};

bool operator==(const MyLinkList::iterator& lhs, const MyLinkList::iterator& rhs) {
    return lhs.base() == rhs.base();
}

bool operator!=(const MyLinkList::iterator& lhs, const MyLinkList::iterator& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const MyLinkList& l) {
    os << "{";
    if (!l.empty()) {
        os << *l.begin();
        auto it = l.begin();
        for (auto i = 1; i < l.size(); i++) {
            ++it;
            os << ", " << *it;
        }
    }
    os << "}";
    return os;
}

#endif // !LINKLIST_H__
