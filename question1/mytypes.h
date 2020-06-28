/*
   File: mytypes.h
   Description: This is the header file with all the declarations for my types
   Course: 150018 C++ Workshop
   Exercise 5, Question 2.2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __MYTYPES_H_
#define __MYTYPES_H_

#include <iostream>
#include <sstream>

using uint = unsigned int;
using cstring = char*;

// convert uint to cstring, used by function to catch error as cstring
cstring convert2Cstr(uint number);

int binarySearch(int arr[], int l, int r, int x);
int binarySearch(uint arr[], int l, int r, uint x);


#endif __MYTYPES_H_