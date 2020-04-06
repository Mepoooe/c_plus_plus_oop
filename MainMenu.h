#ifndef MAIN_MENU_MODULE
#define MAIN_MENU_MODULE

#include <iostream>
#include "ConsoleApi.h"
#include "Model.h"
#include "Menu.h"
#include "Client.h"
#include "Product.h"
#include "Post.h"
#include "Order.h"
#include "Map.h"

class MainMenu
{
private:
	typedef struct { //Структура для элемента меню
		int id; //Столбец и строка консоли
		const char *str; //Наименование пункта меню
		short x;
		short y;
		Model *model;
	} itemMainMenu;

	const enum menuItems { MENU_CLIENT, MENU_PRODUCT, MENU_POST, MENU_MAP, MENU_EXIT };

	
public:
	itemMainMenu menuItemsList[MENU_EXIT+1] = { //положение (x,y), заголовок, указатель на функцию
		{ MENU_CLIENT, " Клиенты ", 0, 0, NULL},
		{ MENU_PRODUCT, " Продукты ", 11, 0, NULL},
		{ MENU_POST, " Отделения почты ", 21, 0, NULL},
		{ MENU_MAP, " Карта ", 38, 0, NULL},
		{ MENU_EXIT, " Выход ", 51, 0, NULL}
	};

	Menu *menu;

	void drawMenu();
	void refreshMainMenu();
	static void renderBorders();

	MainMenu();
	~MainMenu();
};



#endif