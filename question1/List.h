/*
   File: List.h
   Description: this is header file of class List with sub-class Node
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __LIST_H
#define __LIST_H

#include <iostream>
#include "iterators.h"

template <typename T>
class List;

template <typename T> std::ostream& operator <<(std::ostream& out, const List<T>& rhs);
template <typename T> std::istream& operator >>(std::istream& in, List<T>& rhs);

//------------------------------------------------
// Class List - Arbitrary size Lists
// Permits insertion and removal only from the front of the List
//------------------------------------------------
template <typename T>
class List {
    
    protected:
    //--------------------------------------------
    // inner class Node a single element for the Nodeed List
    //--------------------------------------------
    class Node {
    protected:
        T   _value;
        Node* _next;
    public:
        // constructor
        Node(T);
        Node(T, Node*);
        Node(const Node&);
        ~Node();
        // data areas
        T&   value(); // value by reference
        Node* next() const;  // getter
        void  next(Node*);   // setter
    }; //end of class Node

    //template <typename T,typename R>
 
    
public:
    class Iterator : ForwardIterator<Node, T> {
        using ValueType = T;
        using Pointer = Node*;
        using Reference = T&;
        using ForwardIterator<Node, T>::_p;

    private:
        void advance() { _p = _p->next(); }
    public:
        Iterator(Pointer p) : ForwardIterator<Node, T>(p) {}
        Reference operator*() { return _p->value(); }

        bool operator==(const Iterator& rhs) const { return _p == rhs._p; }
        bool operator!=(const Iterator& rhs) const { return _p != rhs._p; }
        Iterator& operator++() { advance(); return *this; }
        Iterator operator++(int) { auto copy(*this); ++(*this); return copy; }

        Iterator& operator = (const Iterator& rhs) { _p = rhs._p; }
    };

    const Iterator begin() const { return Iterator(head); }
    const Iterator end() const { return Iterator(nullptr); }

    // constructors

    // default constructor
    List();

    // copy constructor
    List(const List&);

    // move constructor
    List(List&&);

    // destructor
    ~List();

    // operations

    // Copy assignment
    List& operator = (const List&);

    // move assignment
    List& operator = (List&&);

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
    virtual void clear();

    // insert value by order in list
    void insert(const T value);

    // remove node by value
    void remove(const T value);

    // extraction operator
    friend std::ostream& operator << <>(std::ostream& out, const List& rhs);
    
    // insertion operator
    friend std::istream& operator >> <>(std::istream& in, List& rhs);

    // merge 2 list to new one
    friend List& merge(const List& lst1,const List& lst2);

    // search if there is double value, remove one
    friend List& makeSet(List& lst);

protected:
    // data field
    Node* head = nullptr;
};

/*
// extraction operator
template <typename T> std::ostream& operator << (std::ostream& out, const List<T>& rhs);

// insertion operator
template <typename T> std::istream& operator >> (std::istream& in, List<T>& rhs);
*/
// merge 2 list to new one
template <typename T> List<T>& merge(const List<T>& lst1,const List<T>& lst2);

// search if there is double value, remove one
template <typename T> List<T>& makeSet(List<T>& lst);


//------------------------------------------------
// class Node implementation
//------------------------------------------------
template <typename T>
List<T>::Node::Node(T val) : _value(val) {}

template <typename T>
List<T>::Node::Node(T val, List::Node* nxt) : _value(val), _next(nxt) {}

template <typename T>
List<T>::Node::Node(const List<T>::Node& src) : _value(src._value), _next(src._next) {}

template <typename T>
List<T>::Node::~Node()
{
    next(nullptr);
}

template <typename T>
T& List<T>::Node::value() { return _value; }

template <typename T>
typename List<T>::Node* List<T>::Node::next() const { return _next; }

template <typename T>
void List<T>::Node::next(Node* nxt) { _next = nxt; }

//--------------------------------------------
// class List implementation
//--------------------------------------------

// default constructor
template <typename T>
List<T>::List() : head(nullptr) {}

// copy constructor
template <typename T>
List<T>::List(const List& other) {
    Node* src, * trg;

    // other list is empty
    if (other.head == nullptr)
        head = nullptr;

    // other list isn't empty
    else {
        // create head node
        head = new Node(other.head->value(), nullptr);
        if (head == nullptr)
            throw "failed in memory allocation";

        src = other.head;
        trg = head;
        // loop copy all nodes
        while (src->next() != nullptr) {
            trg->next(new Node(src->next()->value(), nullptr));
            if (trg->next() == nullptr)
                throw "failed in memory allocation";
            src = src->next();
            trg = trg->next();
        }
    }
}

// move constructor
template <typename T>
List<T>::List(List&& other) {
    // Keep the temp list is permanent
    head = other.head;
    // Avoid destructing it in the temporary object
    other.head = nullptr;
}

// destructor
template <typename T>
List<T>::~List() {
    clear();
}

// clear all nodes in list
template <typename T>
void List<T>::clear() {
    // empty all elements from the List
    Node* next;
    for (Node* p = head; p != nullptr; p = next) {
        // delete the element pointed to by p
        next = p->next();
        p->next(nullptr);
        delete p;
    }
    // mark that the List contains no elements 
    head = nullptr;
}

// get bool if list is empty
template <typename T>
bool List<T>::isEmpty() const {
    // test to see if the List is empty
    // List is empty if the head pointer is null
    return head == nullptr;
}

template <typename T>
void List<T>::add(T val) {
    //Add a new value to the front of a Nodeed List
    head = new Node(val, head);
    if (head == nullptr)
        throw "failed in memory allocation";
}

// get value of head
template <typename T>
T List<T>::firstElement() const {
    // return first value in List
    if (isEmpty())
        throw "the List is empty, no first Element";
    return head->value();
}

// search in list by value
template <typename T>
bool List<T>::search(const T val) const {
    // loop to test each element
    for (auto it = begin(); it != end(); ++it)
        if (val == *it)
            return true;
    // not found
    return false;
}


// insert value by order in list
template <typename T>
void List<T>::insert(const T val) {
    Node* p = new Node(val, nullptr);

    if (isEmpty()) {
        head = p;
        return;
    }

    if (head->value() > val) {
        p->next(head);
        head = p;
        return;
    }

    Node* src = head;

    while ((src->next() != nullptr) && (src->next()->value() < val)) {
        src = src->next();
    }

    p->next(src->next());
    src->next(p);

    return;
}

// remove node by value
template <typename T>
void List<T>::remove(const T val) {

    // if the list is empty, can't remove
    if (isEmpty())
        throw "value not found";

    Node* p, * delNode;

    // if the value in head, moving the head to next
    if (head->value() == val) {
        p = head;
        head = head->next();
        p->next(nullptr);
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
    delNode->next(nullptr);
    delete delNode;

    return;
}

// remove first item in list
template <typename T>
void List<T>::removeFirst() {
    // make sure there is a first element
    if (isEmpty())
        throw "the List is empty, no Elements to remove";

    // save pointer to the removed node
    Node* p = head;
    // reassign the first node
    head = p->next();
    p->next(nullptr);
    // recover memory used by the first element
    delete p;
}

// operator = copy assignment
template <typename T>
List<T>& List<T>::operator = (const List& other) {

    if (this == &other)
        return *this;

    Node* src, * trg;

    // if other is null, set null to head
    if (other.head == nullptr) {
        head = nullptr;
    }
    else {
        // copy head
        head = new Node(other.head->value(), nullptr);
        if (head == nullptr)
            throw "failed in memory allocation";

        src = other.head;
        trg = head;

        // loop to copy until end of list
        while (src->next() != nullptr) {
            trg->next(new Node(src->next()->value(), nullptr));
            if (trg->next() == nullptr)
                throw "failed in memory allocation";
            src = src->next();
            trg = trg->next();
        }
    }

    return *this;
}

// operator = move assignment
template <typename T>
List<T>& List<T>::operator = (List&& other) {

    // Keep the temp list is permanent
    head = other.head;

    // Avoid destructing it in the temporary object
    other.head = nullptr;

    return *this;
}

// extraction operator
template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& rhs)
{
    if (rhs.isEmpty())
        return out;

    // loop for cout all items to end of list
    for (typename List<T>::Node* p = rhs.head; p != nullptr; p = p->next())
        out << p->value() << (p->next() != nullptr ? ", " : "");

    return out;
}

// insertion operator
template <typename T>
std::istream& operator>>(std::istream& in, List<T>& rhs)
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

// merge 2 list to new one
template <typename T>
List<T>& merge(const List<T>& lst1, const List<T>& lst2)
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
}

#endif //__LIST_H


