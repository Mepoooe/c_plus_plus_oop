#include "MainMenu.h"
#include "GlobalVars.h"


Client* clientModels;
Product* productModels;
Post* postModels;
Order* orderModels;
PostWarehouse* postWarehouseModels;
Map* map;


MainMenu::MainMenu()
{
	menu = new Menu();
	menu->selectedTextColor = ConsoleApi::clBlack;
	menu->selectedBackgroundColor = ConsoleApi::clLightGreen;

	for (int i = 0; i <= MENU_EXIT; i++)
	{
		menu->addItem(menuItemsList[i].str, menuItemsList[i].x, menuItemsList[i].y, ConsoleApi::clWhite, ConsoleApi::clBlue);
	}

	orderModels = new Order();
	postWarehouseModels = new PostWarehouse();
	map = new Map();
}

void MainMenu::refreshMainMenu()
{
	system("CLS");
	renderBorders();
	menu->draw();
	menu->setSelectedItemById(menu->selected);
}

void MainMenu::drawMenu()
{
	renderBorders();
	menu->setPosition(2, 2);
	menu->draw();

	fflush(stdin); //очистить буфер клавиатуры

	int iKey = 0;
	while (true)
	{
		if (_kbhit())
		{
			iKey = _getch();
			switch (iKey)
			{
			case ConsoleApi::keyRight:
				if (menu->selected < menu->countItem - 1) {
					menu->setSelectedItemById(menu->selected + 1);
				}
				else {
					menu->setSelectedItemById(0);
				}
				StringHelper::showCursor(false);
				break;
			case ConsoleApi::keyLeft:
				if (menu->selected > 0) {
					menu->setSelectedItemById(menu->selected - 1);
				}
				else {
					menu->setSelectedItemById(menu->countItem - 1);
				}
				StringHelper::showCursor(false);
				break;
			case ConsoleApi::keyEnter:
				StringHelper::showCursor(true);
				switch (menu->selected)
				{
				case MENU_CLIENT:
					ConsoleApi::GotoXY(2, 3);

					if (NULL == clientModels)
					{
						clientModels = new Client();
					}

					clientModels->run();

					// назад в главное меню
					refreshMainMenu();

					break;
				case MENU_PRODUCT:
					ConsoleApi::GotoXY(2, 3);

					if (NULL == productModels)
					{
						productModels = new Product();
					}

					productModels->run();

					// назад в главное меню
					refreshMainMenu();

					break;
				case MENU_POST:
					ConsoleApi::GotoXY(2, 3);

					if (NULL == postModels)
					{
						postModels = new Post();
					}

					postModels->run();

					// назад в главное меню
					refreshMainMenu();

					break;
				case MENU_MAP:
					ConsoleApi::GotoXY(25, 3);
					map->run();
					break;
				case MENU_EXIT:
					ConsoleApi::GotoXY(25, 3);
					ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
					int resp;
					printf("¬ы уверены, что хотите выйтииз программы ? (y / n) ? ");
					resp = getchar();
					if (resp == 'y' || resp == 'Y')
					{
						ConsoleApi::GotoXY(0, 0);
						system("cls");
						exit(0);
					}
					//getCursorPosition(); // запомнить положение курсора,
					// если отменили выход
					break;
				}
				//fflush(stdin); //очистить буфер клавиатуры
				//gotoxy(menu[sel].x, menu[sel].y); // курсор в
				//// текущий пункт меню
				//showCursor(false);
				break;
			case ConsoleApi::keyEscape: // выход по клавише ESC
				system("cls");
				exit(0); //завершение программы
			}
		}
	}
}


void MainMenu::renderBorders() {
	for (int i = 0; i < 150; i++)
	{
		ConsoleApi::GotoXY(i, 1);
		printf("_");
	}

	for (int i = 2; i < 80; i++)
	{
		ConsoleApi::GotoXY(22, i);
		printf("|");
	}
}

MainMenu::~MainMenu()
{
	delete menu;

	if (NULL != map)
	{
		delete map;
	}

	if (NULL != orderModels)
	{
		delete orderModels;
	}

	if (NULL != postWarehouseModels)
	{
		delete postWarehouseModels;
	}

	for (int i = 0; i <= MENU_EXIT; i++)
	{
		if (NULL != menuItemsList[i].model)
		{
			delete menuItemsList[i].model;
		}
	}


	if (NULL != postModels)
	{
		delete postModels;
	}


	if (NULL != clientModels)
	{
		delete clientModels;
	}


	if (NULL != productModels)
	{
		delete productModels;
	}

}
