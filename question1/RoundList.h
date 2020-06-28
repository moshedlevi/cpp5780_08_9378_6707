/*
   File: RoundList.h
   Description: this is header file of class RoundList as inherits from class list
                this class if round from tail to head
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __ROUNDLIST_H
#define __ROUNDLIST_H

#include <iostream>
#include "List.h"

class RoundList : public List<int> {
    public:
        // constructors

        // defalut constructor
        RoundList() ;

        // copy constructor
        RoundList(const RoundList&);

        // move constructor
        RoundList(RoundList&&);

        // destructor
        ~RoundList();

        // operations

        // copy assignment
        RoundList& operator = (const RoundList&);

        // move assignment
        RoundList& operator = (RoundList&&);

        // add value in head of list. override of List::add function
        void add(const int value);

        // seach value in RoundList by n *as index*
        // if n > size, the roundlist run over to n
        // if roundlist is empty, return -1, override of List::search function
        int search(const int) const;

        // remove first node in roundlist, override of List::removeFirst function
        void removeFirst();

        // clear all nodes in RoundList, override of List::clear function
        void clear();

        // insert value by order in list, override of List::insert function
        void insert(const int value);

        // remove node by value, override of List::remove function
        void remove(const int value);

        // add value to end of list
        void addToEnd(const int val);
        
        // extraction operator, override of List::<< function
        friend std::ostream& operator << (std::ostream& out, const RoundList& rhs);
      
};

// extraction operator, override of List::<< function
std::ostream& operator << (std::ostream& out, const RoundList& rhs);

#endif __ROUNDLIST_H
