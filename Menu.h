#ifndef MENU_MODULE
#define MENU_MODULE

#include "ConsoleApi.h"
#include "Location.h"
#include "MenuItem.h"

class Menu
{
public:
	static const int maxItems = 10;
	int selected;
	int countItem;

	ConsoleApi::ConsoleColors selectedTextColor = ConsoleApi::clBlack;
	ConsoleApi::ConsoleColors selectedBackgroundColor = ConsoleApi::clWhite;

	MenuItem *items[maxItems];
	Location *position;

	Menu();
	~Menu();

	void setSelectedItemById(int id);
	void clear();
	void draw();
	void setPosition(short x, short y);

	int getCountItem();
	int maxCaptionLength();
	int addItem(const char* caption, short x, short y, ConsoleApi::ConsoleColors textColor, ConsoleApi::ConsoleColors backgroundColor);
};

#endif