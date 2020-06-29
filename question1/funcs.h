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

template <typename T>
void swap(T& varA, T& varB) {
    if (sizeof(varA) <= 4) {
        T tmp = new T(varA);
        varA = varB;
        varB = tmp;
    }
    else {
        char tmp[sizeof(varA)];
        std::memcpy(tmp, &varA, sizeof(varA));
        std::memmove(&varA, &varB, sizeof(varA));
        std::memcpy(&varB, &tmp, sizeof(varA));
    }
}

template <typename I>
I partition(I begin, I end,
    int (*comparator)(typename I::Reference, typename I::Reference)) {

        I i = begin;
        I it = begin;

        while (it != end)
        {
            //if (*it <= *end)
            if (comparator(*it, *end)<=0)
            {
                swap<I::Reference>(*i, *it);
                ++i;
            }
            ++it;
        }

        swap<I::Reference>(*i, *end);
        return i;

}

template <typename I>
void sort(I begin, I end,
    int (*comparator)(typename I::Reference, typename I::Reference)) {
    
        if (begin != end)
        {
            I q = partition<I>(begin, end, comparator); //5
            sort<I>(begin, --q, comparator); //4
            sort<I>(++(++q), end, comparator); //6
        }
}



#endif
