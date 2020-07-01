/*
   File: main.cpp
   Description: this is main program file for test template class BidirectionalList and iterators
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include <iostream>
#include "List.h"
#include "BidirectionalList.h"
//#include "RoundList.h"
#include "menu.h"
#include "funcs.h"


using namespace std;
using ListIt = BidirectionalList<int>::Iterator;

int main() {
	BidirectionalList<int> ls1;
	MenuOption choice;

	while ((choice = menu()) != EXIT) {
		int num;
		switch (choice) {
		case ADD:
			cout << "Enter 5 numbers: ";
			for (int i = 0; i < 5; i++) {
				cin >> num;
				ls1.add(num);
			}
			break;

		case ADD_TO_END:
			cout << "Enter 5 numbers: ";
			for (int i = 0; i < 5; i++) {
				cin >> num;
				ls1.insert(num);
			}
			break;

		case REMOVE_FIRST:
			ls1.removeFirst();
			break;

		case SEARCH:
			cout << "Enter a number: ";
			cin >> num;
			cout << num << " is " << (ls1.search(num)?"":"Not ") << "in list." << endl;
			break;

		case CLEAR:
			ls1.clear();
			break;

		case EMPTY:
			if (ls1.isEmpty())
				cout << "the list is Empty" << endl;
			else
				cout << "the list is Not empty" << endl;
			break;

		case PRINT_LIST:
			{
				List<int>& lsOneDir = ls1;
				for (List<int>::Iterator it = lsOneDir.begin(); it != lsOneDir.end(); ++it) {
					cout << *it << endl;
				}
			}
			break;

		case PRINT_BILIST:

			for (ListIt it = ls1.begin(); it != ls1.end(); ++it) {
				cout << *it << endl;
			}

			break;

		case MAX_VALUE:
			{
				ListIt it = max(ls1.begin(), ls1.end());
				cout << *it << endl;

				break;
			}
		case SORT:
			sort<ListIt>(ls1.begin(), ls1.end(),
				[](typename ListIt::Reference varA, typename ListIt::Reference varB) {
 					if (varA < varB)
						return -1;
					else if (varA == varB)
						return 0;
					else
						return 1; });
			break;
		default:
			cout << "ERROR!" << endl;
		}
	}
	return 0;
}

