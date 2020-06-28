/*
   File: RoundList.cpp
   Description: this is file contains implementation of class RoundList as inherits from class list
                this class if round from tail to head
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include "RoundList.h"

// defalut constructor
RoundList::RoundList() : List<int>() {};

// copy constructor
RoundList::RoundList(const RoundList& other) {
    
    Node* src, * trg;

    // if other RoundList is empty
    if (other.head == nullptr)
        head = nullptr;

    // if other RoundList isn't empty
    else {
        // create head node
        head = new Node(other.head->value(), nullptr);
        if (head == nullptr)
            throw "failed in memory allocation";

        src = other.head;
        trg = head;

        // copy all nodes to the end
        while (src->next() != other.head) {
            trg->next(new Node(src->next()->value(), nullptr));
            if (trg->next() == nullptr)
                throw "failed in memory allocation";

            src = src->next();
            trg = trg->next();
        }

        // set next of last to the head
        trg->next(head);
    }

}

// move constructor
RoundList::RoundList(RoundList&& other)
{
    // Keep the temp list is permanent
    head = other.head;
    // Avoid destructing it in the temporary object
    other.head = nullptr;
}

// destructor
RoundList::~RoundList()
{
    clear();
}

// copy assignment
RoundList& RoundList::operator=(const RoundList& other)
{

    if (this == &other)
        return *this;   

    // if other is null, set null to head
    if (other.head == nullptr)
        head = nullptr;

    else {       
        Node* src, * trg;

        // copy head
        head = new Node(other.head->value(), nullptr);
        if (head == nullptr)
            throw "failed in memory allocation";

        src = other.head;
        trg = head;

        // loop to copy until end of list
        while (src->next() != other.head) {
            trg->next(new Node(src->next()->value(), nullptr));
            if (trg->next() == nullptr)
                throw "failed in memory allocation";
            src = src->next();
            trg = trg->next();
        }

        trg->next(head);
    }

    return *this;
}

// move assignment
RoundList& RoundList::operator=(RoundList&& other)
{
    // Keep the temp list is permanent
    head = other.head;

    // Avoid destructing it in the temporary object
    other.head = nullptr;

    return *this;
}

// add value in head of list - override of List::add function
void RoundList::add(int value)
{
    // add new node with value and ptr to current head
    head = new Node(value, head);
    if (head == nullptr)
        throw "failed in memory allocation";

    Node* end;

    // if next is nullptr, the list was empty, end is ptr to head
    if (head->next() == nullptr) {
        end = head;
    } else {
        // promote end to last node
        end = head->next();

        while (end->next() != head->next())
            end = end->next();
    }

    // set next of end to new head
    end->next(head);
}

// seach value in RoundList by n *as index*
// if n > size, the roundlist run over to n
// if roundlist is empty, return -1
int RoundList::search(int n) const
{
    if (isEmpty())
        return -1;

    Node* node = head;

    // promote i to the index
    for (int i = 0; i < n; ++i)
        node = node->next();

    return node->value();
}

// remove first node in roundlist
void RoundList::removeFirst()
{
    // if the list is empty, can't remove
    if (isEmpty())
        throw "value not found";

    // if only one item is list
    if (head == head->next()) {
        delete head;
        head = nullptr;
        return;
    }

    // ptr to oldHead to delete and end to set next to head
    Node* oldHead = head;
    Node* end = head->next();
    head = oldHead->next();

    // promote end to last node in roundlist
    while (end->next() != oldHead)
            end = end->next();

    // set next of end to head
    end->next(head);

    delete oldHead;

    return;
}

// clear all nodes in RoundList, override of List::clear function
void RoundList::clear()
{
    // empty all elements from the List
    Node* next = nullptr;
    for (Node* p = head; next != head; p = next) {

        // delete the element pointed to by p
        next = p->next();
        delete p;
    }

    // mark that the List contains no elements 
    head = nullptr;
}

// insert value by order in list, override of List::insert function
void RoundList::insert(const int val)
{
    // if list is empty or head value smaller than new value, use add
    if ((isEmpty()) || (head->value() > val)) {
        add(val);
        return;
    }

    // create new node with value
    Node* p = new Node(val, nullptr);
    if (p == nullptr)
        throw "failed in memory allocation";

    Node* src = head;

    // loop for search previous node
    while ((src->next() != head) && (src->next()->value() < val)) {
        src = src->next();
    }

    // set next from previous to new node
    p->next(src->next());

    // set new node as next of previous
    src->next(p);

    return;
}

// remove node by value, override of List::remove function
void RoundList::remove(const int val)
{

    // if the list is empty, can't remove
    if (isEmpty())
        throw "value not found";

    Node* p, * delNode;

    // if the value in head, moving the head to next
    if (head->value() == val) {
        delNode = head;
        p = head;
        head = head->next();
        
        while (p->next() != delNode)
            p = p->next();

        p->next(head);
        
        delete delNode;
        return;
    }

    p = head;

    // loop to check if next isn't and not the value to remove
    while ((p->next() != head) && (p->next()->value() != val))
        p = p->next();

    // if end of list, can't remove
    if (p->next() == head)
        throw "value not found";

    // if the value to remove, move the nextptr to next
    delNode = p->next();
    p->next(delNode->next());
    delNode->next(nullptr);
    delete delNode;

    return;

}

// add value to end of list
void RoundList::addToEnd(int val)
{
    // if empty, add to head
    if (isEmpty()) {
        add(val);
        return;
    }

    // add new node, next pointer to the head for round
    Node* p = new Node(val, head);
    if (p == nullptr)
        throw "failed in memory allocation";

    Node* src = head;

    // promote src to last node
    while (src->next() != head)
        src = src->next();

    // set next of last to new node
    src->next(p);

    return;
}

// extraction operator, override of List::<< function
std::ostream& operator<<(std::ostream& out, const RoundList& rhs)
{
    if (rhs.isEmpty())
        return out;

    // p as pointer of current node
    List<int>::Node* p;

    // loop for print out all nodes, except from last
    for (p = rhs.head; p->next() != rhs.head; p = p->next())
        out << p->value() << (p->next() != rhs.head ? ", "  : "");

    // print out the last value
    out << p->value();

    return out;
}
