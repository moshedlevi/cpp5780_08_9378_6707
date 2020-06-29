/*
   File: main.cpp
   Description: this is main program file for test RoundList class
   Course: 150018 C++ Workshop
   Exercise 8, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include <iostream>
#include "List.h"
#include "BidirectionalList.h"
//#include "RoundList.h"
#include "menu.h"


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
				//ls1.addToEnd(num);
			}
			break;

		case REMOVE_FIRST:
			ls1.removeFirst();
			break;

		case SEARCH:
			cout << "Enter a number: ";
			cin >> num;
			cout << ls1.search(num) << endl;
			break;

		case CLEAR:
			ls1.clear();
			break;

		case EMPTY:
			if (ls1.isEmpty())
				cout << "Empty" << endl;
			else
				cout << "Not empty" << endl;
			break;

		case PRINT_LIST:
			
			for (ListIt it = ls1.begin(); it != ls1.end(); ++it) {
				cout << *it << endl;
			}
			
			break;

		case PRINT_BILIST:

			for (ListIt it = ls1.rbegin(); it != ls1.rend(); --it) {
				cout << *it << endl;
			}

			break;

		default:
			cout << "ERROR!" << endl;
		}
	}
	return 0;
}

