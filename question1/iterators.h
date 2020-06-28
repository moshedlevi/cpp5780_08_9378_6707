/*
   File: iterators.h
   Description: this is header file of class List with sub-class Node
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __ITERATORS_H
#define __ITERATORS_H

template <typename T, typename R>
class ForwardIterator {
protected:
    T* _p;
public:
    using ValueType = R;
    using Pointer = T*;
    using Reference = R&;

    ForwardIterator(Pointer p) : _p(p) {}
    virtual void advance() = 0;
    Reference operator*() { return *_p; }
    Pointer operator->() const { return _p; }
    bool operator==(const ForwardIterator& rhs) const { return _p == rhs._p; }
    bool operator!=(const ForwardIterator& rhs) const { return _p != rhs._p; }
    ForwardIterator& operator++() { advance(); return *this; }
    ForwardIterator operator++(int) { auto copy(*this); ++(*this); return copy; }
    
};

template <typename T, typename R>
class BidirectionalIterator : ForwardIterator<T,R> {
    using ValueType = R;
    using Pointer = T*;
    using Reference = R&;
    using ForwardIterator<T, R>::_p;

    BidirectionalIterator(Pointer p) : ForwardIterator<T, R>(p) {}
    Reference operator*() { return *_p; }
    virtual void advance() = 0;
    virtual void reverse() = 0;
    bool operator==(const BidirectionalIterator& rhs) const { return _p == rhs._p; }
    bool operator!=(const BidirectionalIterator& rhs) const { return _p != rhs._p; }
    BidirectionalIterator& operator++() { advance(); return *this; }
    BidirectionalIterator operator++(int) { auto copy(*this); ++(*this); return copy; }
    BidirectionalIterator& operator--() { reverse(); return *this; }
    BidirectionalIterator operator--(int) { auto copy(*this); --(*this); return copy; }

};


#endif __ITERATORS_H
