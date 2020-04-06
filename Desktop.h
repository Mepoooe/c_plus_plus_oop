#ifndef DESKTOP_MODULE
#define DESKTOP_MODULE

#include "MainMenu.h"
#include <iostream>

class Desktop
{
public:
	MainMenu* mainMenu;
	Desktop();
	void render();
	void renderConsoleBackground();
	void setScreenBufferSize();
	~Desktop();
};

#endif