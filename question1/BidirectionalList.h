/*
   File: BidirectionalList.h
   Description: this is header file of class List with sub-class Node
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __BIDIRECTIONALLIST_H
#define __BIDIRECTIONALLIST_H

#include <iostream>
#include "iterators.h"
#include "List.h"

template <typename T>
class BidirectionalList;

template <typename T> std::ostream& operator <<(std::ostream& out, const BidirectionalList<T>& rhs);
template <typename T> std::istream& operator >>(std::istream& in, BidirectionalList<T>& rhs);

//------------------------------------------------
// Class List - Arbitrary size Lists
// Permits insertion and removal only from the front of the List
//------------------------------------------------
template <typename T>
class BidirectionalList : public List<T> {
public:
    using List<T>::head;
    class Iterator;

    protected:
    //--------------------------------------------
    // inner class Node a single element for the Nodeed List
    //--------------------------------------------
    class Node : public List<T>::Node {
        protected:
            Node* _prev = nullptr;
        public:
            using List<T>::Node::_value;
            using List<T>::Node::next;
            using List<T>::Node::_next;

            // constructor
            Node(T, Node*, Node*);
            Node(const Node&);
            ~Node();
            // data areas
            //T&   value(); // value by reference
            //Node* next() const;  // getter
            //void  next(Node*);   // setter
            Node* prev() const;  // getter
            void  prev(Node*);   // setter
    }; //end of class Node

    //template <typename T,typename R>
protected:
    // data field
    //Node* head = nullptr;
    Node* tail = nullptr;
    
public:
    class Iterator : public BidirectionalIterator<Node, T> {

    private:
        BidirectionalList* _list = nullptr;

    public:
        using ValueType = T;
        using Pointer = Node*;
        using Reference = T&;
        using BidirectionalIterator<Node, T>::_p;

        Iterator(Pointer p) : BidirectionalIterator<Node, T>(p) {}
        Iterator(Pointer p, BidirectionalList* list) : BidirectionalIterator<Node, T>(p), _list(list) {}

    private:
        void advance() override { if (_p == nullptr) _p = (Node*)_list->head; else _p = (Node*)_p->next(); }
        void reverse() override { if (_p == nullptr) _p = _list->tail; else _p = _p->prev(); }

    public:
        Reference operator*() { return _p->value(); }

        bool operator==(const Iterator& rhs) const { return _p == rhs._p; }
        bool operator!=(const Iterator& rhs) const { return _p != rhs._p; }
        Iterator& operator++() { advance(); return *this; }
        Iterator operator++(int) { auto copy(*this); ++(*this); return copy; }
        Iterator& operator--() { reverse(); return *this; }
        Iterator operator--(int) { auto copy(*this); --(*this); return copy; }

        Iterator& operator = (const Iterator& rhs) { _p = rhs._p; _list = rhs._list; return *this; }
    };

    // constructors

    // default constructor
    BidirectionalList();

    // copy constructor
    BidirectionalList(const BidirectionalList&);

    // move constructor
    BidirectionalList(BidirectionalList&&);

    // destructor
    //~BidirectionalList();

    // operations

    // Copy assignment
    BidirectionalList& operator = (const BidirectionalList&);

    // move assignment
    BidirectionalList& operator = (BidirectionalList&&);

    // add value to end of list
    void add(T value);

    // get value of head
    T firstElement() const;

    // search in list by value
    bool search(const T) const;

    // get bool if list is empty
    bool isEmpty() const;

    // remove first item in list
    void removeFirst();

    // clear all nodes in list
    void clear();

    // insert value by order in list
    void insert(const T value);

    // remove node by value
    void remove(const T value);

    const Iterator begin() const { return BidirectionalList<T>::Iterator((Node*)head,*this); }
    const Iterator end() const { return BidirectionalList<T>::Iterator(nullptr, *this); }
    const Iterator rbegin() const { return BidirectionalList<T>::Iterator(tail,*this); }
    const Iterator rend() const { return BidirectionalList<T>::Iterator(nullptr,*this); }

    // extraction operator
    friend std::ostream& operator << <>(std::ostream& out, const BidirectionalList& rhs);
    
    // insertion operator
    friend std::istream& operator >> <>(std::istream& in, BidirectionalList& rhs);
    /*
    // merge 2 list to new one
    friend BidirectionalList& merge(const BidirectionalList& lst1,const BidirectionalList& lst2);

    // search if there is double value, remove one
    friend BidirectionalList& makeSet(BidirectionalList& lst);
    */

};


//------------------------------------------------
// class Node implementation
//------------------------------------------------
template <typename T>
BidirectionalList<T>::Node::Node(T val, Node* nxt, Node* prv) : List<T>::Node(val,(typename List<T>::Node*)nxt), _prev(prv) {}

template <typename T>
BidirectionalList<T>::Node::Node(const Node& src) : List<T>::Node(src) ,_prev(src._prev) {}

template <typename T>
BidirectionalList<T>::Node::~Node()
{
    prev(nullptr);
}

//template <typename T>
//T& List<T>::Node::value() { return _value; }

//template <typename T>
//typename BidirectionalList<T>::Node* Node::next() const { return _next; }

template <typename T>
typename BidirectionalList<T>::Node* BidirectionalList<T>::Node::prev() const { return _prev; }

//template <typename T>
//void BidirectionalList<T>::Node::next(Node* nxt) { _next = (typename List<T>::Node)nxt; }

template <typename T>
void BidirectionalList<T>::Node::prev(Node* prv) { _prev = prv; }

//--------------------------------------------
// class List implementation
//--------------------------------------------


// default constructor
template <typename T>
BidirectionalList<T>::BidirectionalList() : List<T>() {}


// copy constructor
template <typename T>
BidirectionalList<T>::BidirectionalList(const BidirectionalList& other) {
    Node* src, * trg, *newNode;

    // other list is empty
    if (other.head == nullptr)
        head = nullptr;

    // other list isn't empty
    else {
        // create head node
        head = new Node(other.head->value(), nullptr, nullptr);
        if (head == nullptr)
            throw "failed in memory allocation";

        src = other.head;
        trg = head;
        // loop copy all nodes
        while (src->next() != nullptr) {
            newNode = new Node(src->next()->value(), nullptr, trg);
            trg->next((typename List<T>::Node)newNode);
            if (trg->next() == nullptr)
                throw "failed in memory allocation";

            src = src->next();
            trg = trg->next();
        }

        tail = trg;

    }
}

// move constructor
template <typename T>
BidirectionalList<T>::BidirectionalList(BidirectionalList&& other) {
    // Keep the temp list is permanent
    head = other.head;
    tail = other.tail;
    // Avoid destructing it in the temporary object
    other.head = nullptr;
    other.tail = nullptr;
}

/*
// destructor
template <typename T>
List<T>::~List() {
    clear();
}
*/

// clear all nodes in list
template <typename T>
void BidirectionalList<T>::clear() {
    // empty all elements from the List
    Node* next;
    for (Node* p = (Node*)head; p != nullptr; p = next) {
        // delete the element pointed to by p
        next = (Node*)p->next();
        p->next(nullptr);
        p->prev(nullptr);
        delete p;
    }
    // mark that the List contains no elements 
    head = nullptr;
    tail = nullptr;
}

// get bool if list is empty
template <typename T>
bool BidirectionalList<T>::isEmpty() const {
    // test to see if the List is empty
    // List is empty if the head pointer is null
    return head == nullptr;
}

template <typename T>
void BidirectionalList<T>::add(T val) {
    //Add a new value to the front of a Nodeed List

    Node* oldHead = (Node*)head;
    head = new Node(val, (Node*)head, nullptr);

    if (tail == nullptr)
        tail = (Node*)head;

    if (oldHead != nullptr)
        oldHead->prev((Node*)head);

    if (head == nullptr)
        throw "failed in memory allocation";
}


// get value of head
template <typename T>
T BidirectionalList<T>::firstElement() const {
    // return first value in List
    if (isEmpty())
        throw "the List is empty, no first Element";

    return head->value();
}

/*
// search in list by value
template <typename T>
bool BidirectionalList<T>::search(const T& val) const {
    // loop to test each element
    for (BiNode* p = head; p != nullptr; p = p->next())
        if (val == p->value())
            return true;
    // not found
    return false;
}*/
// search in list by value
template <typename T>
bool BidirectionalList<T>::search(const T val) const {
    // loop to test each element
    for (auto it = begin(); it != end(); ++it)
        if (val == *it)
            return true;
    // not found
    return false;
}

// insert value by order in list
template <typename T>
void BidirectionalList<T>::insert(const T val) {
    Node* p = new Node(val, nullptr, nullptr);

    if (isEmpty()) {
        head = p;
        tail = p;
        return;
    }

    if (head->value() > val) {
        p->next((typename List<T>::Node)head);
        head->prev(p);
        head = p;
        return;
    }

    Node* src = head;

    while ((src->next() != nullptr) && (src->next()->value() < val)) {
        src = src->next();
    }

    p->next((typename List<T>::Node)src->next());
    p->prev(src);
    src->next()->prev(p);
    src->next((typename List<T>::Node)p);

    if (p->next() == nullptr)
        tail = p;

    return;
}

// remove node by value
template <typename T>
void BidirectionalList<T>::remove(const T val) {

    // if the list is empty, can't remove
    if (isEmpty())
        throw "value not found";

    Node* p, * delNode;

    // if the value in head, moving the head to next
    if (head->value() == val) {
        p = head;
        head = head->next();

        if (head != nullptr) {
            head->prev(nullptr);
        }
        else {
            tail = nullptr;
        }
           
        p->next(nullptr);
        p->prev(nullptr);
        delete p;
        return;
    }

    p = head;

    // loop to check if next isn't and not the value to remove
    while ((p->next() != nullptr) && (p->next()->value() != val))
        p = p->next();

    // if end of list, can't remove
    if (p->next() == nullptr)
        throw "value not found";

    // if the value to remove, move the nextptr to next
    delNode = p->next();
    p->next(delNode->next());

    if (p->next() == nullptr) {
        tail = p;
    }
    else {
        p->next()->prev(p);
    }

    delNode->next(nullptr);
    delNode->prev(nullptr);
    delete delNode;

    return;
}

// remove first item in list
template <typename T>
void BidirectionalList<T>::removeFirst() {
    // make sure there is a first element
    if (isEmpty())
        throw "the List is empty, no Elements to remove";

    // save pointer to the removed node
    Node* p = (Node*)head;
    // reassign the first node
    head = (Node*)p->next();
    if (head != nullptr) {
        static_cast<Node*>(head)->prev(nullptr);
    }
    else {
        tail = nullptr;
    }
    
    p->next(nullptr);
    p->prev(nullptr);
    // recover memory used by the first element
    delete p;
}

// operator = copy assignment
template <typename T>
BidirectionalList<T>& BidirectionalList<T>::operator = (const BidirectionalList& other) {

    if (this == &other)
        return *this;

    Node* src, * trg, *newNode;

    // if other is null, set null to head
    if (other.head == nullptr){
        head = nullptr;
        tail = nullptr;
    }
    else {
        // copy head
        head = new Node(other.head->value(), nullptr, nullptr);
        if (head == nullptr)
            throw "failed in memory allocation";

        src = other.head;
        trg = head;

        // loop to copy until end of list
        while (src->next() != nullptr) {
            newNode = new Node(src->next()->value(), nullptr, trg);
            trg->next((typename List<T>::Node)newNode);
            if (trg->next() == nullptr)
                throw "failed in memory allocation";
            src = src->next();
            trg = trg->next();
        }

        tail = trg;
    }

    return *this;
}

// operator = move assignment
template <typename T>
BidirectionalList<T>& BidirectionalList<T>::operator = (BidirectionalList&& other) {

    // Keep the temp list is permanent
    head = other.head;
    tail = other.tail;

    // Avoid destructing it in the temporary object
    other.head = nullptr;
    other.tail = nullptr;

    return *this;
}

// extraction operator
template <typename T>
std::ostream& operator<<(std::ostream& out, const BidirectionalList<T>& rhs)
{
    if (rhs.isEmpty())
        return out;

    // loop for cout all items to end of list
    for (typename BidirectionalList<T>::Node* p = rhs.head; p != nullptr; p = p->next())
        out << p->value() << (p->next() != nullptr ? ", " : "");

    return out;
}

// insertion operator
template <typename T>
std::istream& operator>>(std::istream& in, BidirectionalList<T>& rhs)
{
    int val, last;
    in >> val;

    // loop for insert while new value is larger than previous
    do {
        last = val;
        rhs.insert(val);
        in >> val;
    } while (val > last);

    return in;
}

/*
// merge 2 list to new one
template <typename T>
BidirectionalList<T>& merge(const BidirectionalList<T>& lst1, const BidirectionalList<T>& lst2)
{
    List* newList = new List;
    List::Node* n1, * n2;
    n1 = lst1.head;
    n2 = lst2.head;

    // loop while any of list isn't end
    while ((n1 != nullptr) || (n2 != nullptr)) {

        // if end of lst1 or value of lst1 grather than lst2, insert from lst2
        if ((n1 == nullptr) || ((n2 != nullptr) && (n1->value() > n2->value()))) {
            newList->insert(n2->value());
            n2 = n2->next();
        }
        // if end of lst2 or value of lst1 smaller than lst2, insert from lst1
        else {
            newList->insert(n1->value());
            n1 = n1->next();
        }
    }

    return *newList;
}

// search if there is double value, remove one
template <typename T>
List<T>& makeSet(List<T>& lst)
{
    List::Node* p, * delNode;

    p = lst.head;

    // loop to the end
    while (p != nullptr) {
        // if next isn't null, and current value equal to next, remove
        if ((p->next() != nullptr) && (p->value() == p->next()->value())) {
            delNode = p->next();
            p->next(p->next()->next());
            delNode->next(nullptr);
            delete delNode;
        }

        p = p->next();
    }

    return lst;
}*/

#endif //__BIDIRECTIONALLIST_H


