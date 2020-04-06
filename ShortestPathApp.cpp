#include "pch.h"
#include <iostream>
#include "globalVars.h"


Desktop *mainDesktop;

int main()
{
	
	mainDesktop = new Desktop();

	mainDesktop->render();

	delete mainDesktop;
}