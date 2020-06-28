/*
   File: menu.cpp
   Description: this is implement file of enum for menu options
   Course: 150018 C++ Workshop
   Exercise 6, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include<iostream>
#include<iomanip>
#include"menu.h"

using namespace std;

MenuOption operator++(MenuOption& rhs) {
	rhs = MenuOption(int(rhs) + 1);
	return rhs;
}

const char* MenuOptionLine[LAST_MENU_OPTION + 1] {
	"Exit",
	"Add to the beginning of the list",
	"Add to the end of the list",
	"Remove first from list",
	"Search in the list",
	"Clear the list",
	"Check whether the list is empty",
	"Print out the list"
};

istream& operator>>(istream& in, MenuOption& rhs) {
	int value;
	in >> value;
	rhs = MenuOption(value);
	return in;
}

ostream& operator<<(ostream& out, MenuOption rhs) {
	out << setw(4) << int(rhs) << "\t--\t" << MenuOptionLine[rhs];
	return out;
}

MenuOption menu() {
	MenuOption chosen;

	cout << endl << "Menu options:" << endl << endl;

	for (chosen = FIRST_MENU_OPTION; chosen <= LAST_MENU_OPTION; ++chosen)
		cout << chosen << endl;
	cout << endl;

	cout << "Please choose a menu option: ";
	cin >> chosen;
	return chosen;
}