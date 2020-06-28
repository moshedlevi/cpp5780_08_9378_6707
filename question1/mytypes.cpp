/*
   File: mytypes.cpp
   Description: this is file include some help functions, mainly binarySearch for different types
   Course: 150018 C++ Workshop
   Exercise 6, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include <iomanip>
#include "mytypes.h"

using namespace std;

// convert uint to cstring, used by function to catch error as cstring
cstring convert2Cstr(uint number) {

	// calc length of number and init dynamic cstring in same length (+1 to \0)
	int digits = (int)log10((double)number) + 1;
	cstring text = new char[digits + 1];

	stringstream sstream;

	// inseration the number into sstream to using as stream
	sstream << number;

	// extraction the number from sstream into cstring
	sstream >> text;
	
	// set 0 flag at end of cstring
	text[digits] = 0;

	return text;
}

// binary search to fine int in array base on X
// l = leftIndex, r = rightIndex
int binarySearch(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle 
		// itself 
		if (arr[mid] == x)
			return mid;

		// If element is smaller than mid, then 
		// it can only be present in left subarray 
		if (arr[mid] > x)
			return binarySearch(arr, l, mid - 1, x);

		// Else the element can only be present 
		// in right subarray 
		return binarySearch(arr, mid + 1, r, x);
	}

	// We reach here when element is not 
	// present in array 
	return -1;
}

// binary search to fine uint in array base on X
// l = leftIndex, r = rightIndex
int binarySearch(uint arr[], int l, int r, uint x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle 
		// itself 
		if (arr[mid] == x)
			return mid;

		// If element is smaller than mid, then 
		// it can only be present in left subarray 
		if (arr[mid] > x)
			return binarySearch(arr, l, mid - 1, x);

		// Else the element can only be present 
		// in right subarray 
		return binarySearch(arr, mid + 1, r, x);
	}

	// We reach here when element is not 
	// present in array 
	return -1;
}
