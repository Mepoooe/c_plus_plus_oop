#include "Product.h"

Product::Product() {
	menu = new Menu();
	for (int i = 0; i <= MENU_SAVE_TO_FILE; i++)
	{
		menu->addItem(menuItemsList[i].str, menuItemsList[i].x, menuItemsList[i].y, ConsoleApi::clWhite, ConsoleApi::clBlue);
	}
}

void Product::run() {
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
					addNewProduct();
					break;
				case MENU_SHOW:
					cleanContent();
					showAllProducts();
					break;
				case MENU_DELETE:
					deleteProduct();
					break;
				case MENU_SAVE_TO_FILE:
					saveProductToFile();
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

void Product::fillMenuItem(Menu* newMenu, Model* item, int x, int y) {
	Product* product = (Product*)item;
	newMenu->addItem(product->name, x, y++, ConsoleApi::clWhite, ConsoleApi::clBlue);
}

void Product::addNewProduct()
{
	Product* newProduct = new Product();

	newProduct->id = getLastIndex();
	int i = 0;

	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i++);
	printf("Введите название продукта: ");
	newProduct->name = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(newProduct->name, stringLength);
	scanf_s("%s", newProduct->name, stringLength);

	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i++);
	printf("Введите описание продукта: ");
	newProduct->description = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(newProduct->description, stringLength);
	scanf_s("%s", newProduct->description, stringLength);

	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i++);
	printf("Введите цену продукта: ");
	scanf_s("%f", &newProduct->price, stringLength);


	add(newProduct);
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i++);
	printf("Продукт добавлен!");
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + 100);
}

void Product::showAllProducts()
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf("Список продуктов! \n");

	Product* products = (Product*)list;
	int i = 2;
	if (NULL == products)
	{
		ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
		printf("Список продуктов пуст!");
	}
	else {
		while (NULL != products)
		{
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
			printf("ID: %d; Название: %s; Описание: %s; Цена: %.2f \n", products->id, products->name, products->description, products->price);
			products = (Product*)products->next;
			i++;
		}
	}
}

void Product::printToFile(FILE* fileHandle, Model* item)
{
	Product* product = (Product*)item;
	fprintf(fileHandle, "%d|%s|%s|%f\n", product->id, product->name, product->description, product->price);
}

void Product::saveProductToFile()
{
	saveModelToFile("Продукты.txt");

	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf(" Продукты сохранены в файл! \n");
}

Product* Product::findProductById(int id)
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);

	Model* products = list;
	Product* foundProduct = NULL;

	if (NULL != products)
	{
		while (products)
		{
			Product* product = static_cast<Product*>(products);//from parent to child
			if (product->id == id)
			{
				return product;
			}
			products = products->next;
		}
	}

	return NULL;
}

void Product::deleteProduct()
{
	cleanContent();
	int i = locationForContent->y;
	std::string exitChar = "-1";

	ConsoleApi::GotoXY(locationForContent->x, i);
	printf("Удаление! \n");

	ConsoleApi::GotoXY(locationForContent->x, i += 2);
	printf("Укажите ID продукта которого хотите удалить. Либо напишити '*' для удаление всех продуктов.");

	ConsoleApi::GotoXY(locationForContent->x, ++i);
	printf("Напишити '-1' для возврата в меню.\n");

	ConsoleApi::GotoXY(locationForContent->x, ++i);
	printf("Укажите ID продукта: ");

	char* tempString = (char*)malloc(stringLength * sizeof(char));

	StringHelper::strInput(tempString, stringLength);

	if (StringHelper::strIsNumeric(tempString, stringLength))
	{
		int id = atoi(tempString);
		Product* client = findProductById(id);

		if (NULL == client)
		{
			cleanContent();
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
			printf("Продукт с ID = %d не найден! Пожалуйста попробуйте еще раз.", id);
			Sleep(3000);
			Product::deleteProduct();
		}

		ConsoleApi::GotoXY(locationForContent->x, ++i);
		printf("Вы уверенны что хотите удалить продукт: \"%s\" ? (y / n) ?", client->name);

		char resp = getchar();
		if (resp == 'y' || resp == 'Y')
		{
			deleteByIndex(client->id - 1);
			cleanContent();
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
			printf("продукт был удален.");
			Sleep(3000);
			Product::deleteProduct();
		}

		Product::deleteProduct();
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
				Product::deleteProduct();
			}
		}


	}

	free(tempString);
}


Product::~Product() {
	if (NULL != name)
	{
		free(name);
	}

	if (NULL != description)
	{
		free(description);
	}

	delete menu;
}