/*
   File: funcs.h
   Description: this is header file of class List with sub-class Node
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __FUNCS_H
#define __FUNCS_H

template <typename I>
I max(I first, I last) { // not including last
    if (first == last) return last;
    I iMax = first;
    for (++first; first != last; ++first)
        if (*iMax < *first)
            iMax = first;
    return iMax;
}


#endif
