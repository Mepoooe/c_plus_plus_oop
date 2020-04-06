#ifndef MENU_ITEM_MODULE
#define MENU_ITEM_MODULE

#include "Location.h"
#include "StringHelper.h"
#include "ConsoleApi.h"
#include <windows.h>
#include <conio.h> 
#include <iostream> 

class MenuItem
{
public:
	const static int captionLength = 40;
	int id;
	char* caption;
	Location* position;
	ConsoleApi::ConsoleColors textColor;
	ConsoleApi::ConsoleColors backgroundColor;

	void setPosition(short x, short y);

	MenuItem();
	~MenuItem();
};

#endif