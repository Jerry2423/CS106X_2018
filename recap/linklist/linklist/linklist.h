#ifndef LINKLIST_H__
#define LINKLIST_H__


#include <iostream>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <memory>

template<typename T>
struct ListNode {
    T data;
    ListNode<T>* next;
};

//TODO: template, < operator, const correctness.
template<typename T>
class MyLinkList {
    public:
        using data_type = T;
        using size_type = size_t;
        using reference = data_type&;
        using const_reference = const data_type&;
        using node_ptr = ListNode<T>*;
        // using iterator = node_ptr;
        // using const_iterator = const node_ptr;
        
        //default constructor
        MyLinkList() : front_(nullptr), length_(0) {}
        //destrctor
        ~MyLinkList() {
            clean();
        } 
        //copy constructor
        MyLinkList(const MyLinkList& other) : length_(other.size()) {
            if (other.size() > 0) {
                node_ptr curr = other.front_;
                front_ = new ListNode<data_type> {curr->data, nullptr};
                node_ptr temp = front_;
                curr = curr->next;
                while (curr != nullptr) {
                    //create newnode
                    //set temp->next = new node
                    temp->next = new ListNode<data_type> {curr->data, nullptr};
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
                front_ = new ListNode<data_type> {*init.begin(), nullptr};
                node_ptr temp = front_;
                for (auto i = init.begin()+1; i != init.end(); ++i) {
                    temp->next = new ListNode<data_type> {*i, nullptr};
                    temp = temp->next;
                }
            } else {
                front_ = nullptr;
            }
        }

        //push_front_
        void push_front(const data_type& value) {
            if (empty()) {
                front_ = new ListNode<data_type>{value, nullptr};
                length_ += 1;
            } else {
                node_ptr temp = new ListNode<data_type>{value, front_};
                front_ = temp;
                length_ += 1;
            }
        }
        //pop_front
        void pop_front() {
            if (!empty()) {
                node_ptr temp = front_;
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
                node_ptr base() const {
                    return pointee_;
                }
                //next
                node_ptr next() const {
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
                //constructor: it(node_ptr pointee): private: only friend can construc
                iterator(node_ptr pointee) : pointee_(pointee) {};
                node_ptr pointee_;
        };
        //insert_after
        iterator insert_after(iterator it, const data_type& value) {
           auto temp = it.pointee_->next;
           it.pointee_->next = new ListNode<data_type>{value, temp};
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
                front_ = new ListNode<data_type> {value, nullptr};
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
        static void deleteFrom(node_ptr head) {
            if (!head) {
                return;
            } else {
                deleteFrom(head->next);
                delete head;
            }
        }

        node_ptr reverseHelper(node_ptr curr, node_ptr prev) {
            if (!curr->next) {
                curr -> next = prev;
                return curr;
            }
            // node_ptr new_head = reverseHelper(curr->next, curr);
            // curr->next = prev;
            // return new_head;
            //better tail recursion way
            auto temp = curr->next;
            curr->next = prev;
            return reverseHelper(temp, curr);
        }

        node_ptr front_;
        size_type length_;
};

template<typename T>
bool operator==(const typename MyLinkList<T>::iterator& lhs, const typename MyLinkList<T>::iterator& rhs) {
    return lhs.base() == rhs.base();
}

template<typename T>
bool operator!=(const typename MyLinkList<T>::iterator& lhs, const typename MyLinkList<T>::iterator& rhs) {
    return !(lhs == rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyLinkList<T>& l) {
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
