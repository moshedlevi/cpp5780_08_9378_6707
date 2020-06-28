/*
   File: menu.h
   Description: this is header file of enum for menu options
   Course: 150018 C++ Workshop
   Exercise 6, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __MENU_H
#define __MENU_H

enum MenuOption {
	 EXIT, ADD, ADD_TO_END, REMOVE_FIRST, SEARCH, CLEAR, EMPTY, PRINT,
	 FIRST_MENU_OPTION = EXIT, LAST_MENU_OPTION = PRINT
};

MenuOption menu();

#endif // __MENU_H