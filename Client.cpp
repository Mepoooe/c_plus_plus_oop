#include "Client.h"
#include "globalVars.h"
#include "Order.h"
#include <stdio.h>

Client::Client() {
	menu = new Menu();
	for (int i = 0; i <= MENU_SAVE_TO_FILE; i++)
	{
		menu->addItem(menuItemsList[i].str, menuItemsList[i].x, menuItemsList[i].y, ConsoleApi::clWhite, ConsoleApi::clBlue);
	}

	location = new Location(0, 0);
}

void Client::run() {
	menu->draw();

	fflush(stdin); //очистить буфер клавиатуры

	int iKey = 0;
	bool notExit = true;

	while (notExit)
	{
		if (_kbhit())
		{
			iKey = _getch();
			switch (iKey)
			{
			case ConsoleApi::keyDown:
				if (menu->selected < menu->countItem - 1) {
					menu->setSelectedItemById(menu->selected + 1);
				}
				else {
					menu->setSelectedItemById(0);
				}
				StringHelper::showCursor(false);
				break;
			case ConsoleApi::keyUp:
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
				case MENU_BACK:
					notExit = false;
					break;
				case MENU_ADD:
					cleanContent();
					addNewClient();
					break;
				case MENU_ADD_PRODUCT:
					cleanContent();
					addProductForClient();
					break;
				case MENU_SHOW:
					cleanContent();
					showAllClients();
					break;
				case MENU_DELETE:
					deleteClient();
					break;
				case MENU_SAVE_TO_FILE:
					saveClientToFile();
					break;
				}
				break;
			case ConsoleApi::keyEscape: // выход по клавише ESC
				system("cls");
				notExit = false;
			}
		}
	}
}

void Client::fillMenuItem(Menu* newMenu, Model* item, int x, int y) {
	Client* client = (Client*)item;
	newMenu->addItem(client->name, x, y++, ConsoleApi::clWhite, ConsoleApi::clBlue);
}

void Client::addProductForClient()
{
	Menu* clientMenu = clientModels->initMenu();

	printf("Выберите клиента: \n");
	clientMenu->draw();

	Client* client = (Client*)Client::selectNeedleModel(clientMenu, clientModels);
	delete clientMenu;

	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	cleanContent();

	Menu* productMenu = productModels->initMenu();
	productMenu->draw();

	Product* product = (Product*)selectNeedleModel(productMenu, productModels);

	delete productMenu;

	Order* newOrder = new Order();
	newOrder->client = client;
	newOrder->product = product;

	orderModels->add(newOrder);
	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	cleanContent();
}

void Client::addNewClient()
{
	Client* newClient = new Client();

	newClient->id = getLastIndex();
	int x = locationForContent->x;
	int y = locationForContent->y;

	ConsoleApi::GotoXY(x, y++);
	printf("Enter name: ");
	newClient->name = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(newClient->name, stringLength);
	scanf_s("%s", newClient->name, stringLength);

	ConsoleApi::GotoXY(x, y++);
	printf("Enter address: ");
	newClient->address = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(newClient->address, stringLength);
	scanf_s("%s", newClient->address, stringLength);

	ConsoleApi::GotoXY(x, y++);
	printf("Введите X между 0 и 90: ");
	scanf_s("%d", &newClient->location->x);

	ConsoleApi::GotoXY(x, y++);
	printf("Введите Y между 0 и 75: ");
	scanf_s("%d", &newClient->location->y);

	add(newClient);
	ConsoleApi::GotoXY(x, y + 2);
	printf("Client added!");
	ConsoleApi::GotoXY(x, y + 100);
}

void Client::showAllClients()
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf("Список клиентов: \n");

	Client* clients = (Client*)list;
	int i = 2;
	if (NULL == clients)
	{
		ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
		printf("Список клиентов пуст!");
	}
	else {
		while (NULL != clients)
		{
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
			printf("ID: %d; Name: %s; Address: %s;\n", clients->id, clients->name, clients->address);

			Order* orders = (Order*)orderModels->getFirst();

			ConsoleApi::GotoXY(locationForContent->x, ++locationForContent->y + i);
			printf("Список продуктов: \n");
			locationForContent->x++;
			while (NULL != orders)
			{
				ConsoleApi::GotoXY(locationForContent->x, ++locationForContent->y + i);
				if (orders->client->id == clients->id)
				{
					printf("ID: %d; наименование: %s; цена: %f;\n", orders->product->id, orders->product->name, orders->product->price);
				}

				orders = (Order*)orders->next;
			}
			locationForContent->x--;
			locationForContent->y++;
			clients = (Client*)clients->next;
			i++;
		}
	}
}

void Client::printToFile(FILE* fileHandle, Model* item)
{
	Client* client = (Client*)item;
	fprintf(fileHandle, "%d|%s|%s\n", client->id, client->name, client->address);
}

void Client::saveClientToFile()
{
	saveModelToFile("Клиенты.txt");

	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf(" Клиенты сохранены в файл! \n");
}

Client* Client::findClientById(int id)
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);

	Model* clients = list;
	Client* foundClient = NULL;

	if (NULL != clients)
	{
		while (clients)
		{
			Client* client = static_cast<Client*>(clients);//from parent to child
			if (client->id == id)
			{
				return client;
			}
			clients = clients->next;
		}
	}

	return NULL;
}

void Client::deleteClient()
{
	cleanContent();
	int i = locationForContent->y;
	std::string exitChar = "-1";

	ConsoleApi::GotoXY(locationForContent->x, i);
	printf("Удаление! \n");

	ConsoleApi::GotoXY(locationForContent->x, i += 2);
	printf("Укажите ID клиента которого хотите удалить. Либо напишити '*' для удаление всех клиентов.");

	ConsoleApi::GotoXY(locationForContent->x, ++i);
	printf("Напишити '-1' для возврата в меню.\n");

	ConsoleApi::GotoXY(locationForContent->x, ++i);
	printf("Укажите ID клиента: ");

	char* tempString = (char*)malloc(stringLength * sizeof(char));

	StringHelper::strInput(tempString, stringLength);

	if (StringHelper::strIsNumeric(tempString, stringLength))
	{
		int id = atoi(tempString);
		Client* client = findClientById(id);

		if (NULL == client)
		{
			cleanContent();
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
			printf("Клиент с ID = %d не найден! Пожалуйста попробуйте еще раз.", id);
			Sleep(3000);
			Client::deleteClient();
		}

		ConsoleApi::GotoXY(locationForContent->x, ++i);
		printf("Вы уверенны что хотите удалить клиента: \"%s\" ? (y / n) ?", client->name);

		char resp = getchar();
		if (resp == 'y' || resp == 'Y')
		{
			deleteByIndex(client->id - 1);
			cleanContent();
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
			printf("Клиент был удален.");
			Sleep(3000);
			Client::deleteClient();
		}

		Client::deleteClient();
	}
	else {
		cleanContent();
		bool isDeleteAll = strcmp(tempString, "*") == 0;

		if (isDeleteAll)
		{
			deleteAll();
		}
		else {
			bool isExit = strcmp(tempString, "-1") == 0;
			if (isExit == false)
			{
				ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
				printf("Введите число!");
				Sleep(3000);
				Client::deleteClient();
			}
		}


	}

	free(tempString);
}

Client::~Client() {
	delete location;

	if (NULL != name)
	{
		free(name);
	}

	if (NULL != address)
	{
		free(address);
	}

	delete menu;
}