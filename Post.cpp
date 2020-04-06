#include "Post.h"
#include "globalVars.h"

Post::Post() {
	menu = new Menu();
	for (int i = 0; i <= MENU_SAVE_TO_FILE; i++)
	{
		menu->addItem(menuItemsList[i].str, menuItemsList[i].x, menuItemsList[i].y, ConsoleApi::clWhite, ConsoleApi::clBlue);
	}

	location = new Location(0, 0);
}

void Post::run() {
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
				case Post::MENU_BACK:
					notExit = false;
					break;
				case Post::MENU_SHOW:
					cleanContent();
					showAllPosts();
					break;
				case Post::MENU_ADD_PRODUCT:
					cleanContent();
					addProductToPostWarehouse();
					break;
				case Post::MENU_ADD:
					cleanContent();
					addNewPost();
					break;
				case Post::MENU_DELETE:
					deletePost();
					break;
				case Post::MENU_SAVE_TO_FILE:
					savePostToFile();
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

void Post::addNewPost()
{
	Post* newPost = new Post();

	newPost->id = getLastIndex();
	int x = locationForContent->x;
	int y = locationForContent->y;

	ConsoleApi::GotoXY(x, y++);
	printf("Enter name: ");
	newPost->name = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(newPost->name, stringLength);
	scanf_s("%s", newPost->name, stringLength);

	ConsoleApi::GotoXY(x, y++);
	printf("Enter address: ");
	newPost->address = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(newPost->address, stringLength);
	scanf_s("%s", newPost->address, stringLength);

	ConsoleApi::GotoXY(x, y++);
	printf("Введите X между 0 и 90: ");
	scanf_s("%hd", &newPost->location->x);

	ConsoleApi::GotoXY(x, y++);
	printf("Введите Y между 0 и 75: ");
	scanf_s("%hd", &newPost->location->y);

	add(newPost);
	ConsoleApi::GotoXY(x, y + 2);
	printf("Post added!");
	ConsoleApi::GotoXY(x, y + 100);
	cleanContent();
}

void Post::showAllPosts()
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf("Post List! \n");

	Post* Posts = (Post*)list;
	int i = 2;
	if (NULL == Posts)
	{
		ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
		printf("List of Posts is empty!");
	}
	else {
		while (NULL != Posts)
		{
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
			printf("ID: %d; Name: %s; Address: %s;\n", Posts->id, Posts->name, Posts->address);
			Posts = (Post*)Posts->next;
			i++;
		}
	}
}

void Post::printToFile(FILE* fileHandle, Model* item)
{
	Post* post = (Post*)item;
	fprintf(fileHandle, "%d|%s|%s\n", post->id, post->name, post->address);
}

void Post::fillMenuItem(Menu* newMenu, Model* item, int x, int y) {
	Post* client = (Post*)item;
	newMenu->addItem(client->name, x, y++, ConsoleApi::clWhite, ConsoleApi::clBlue);
}


void Post::addProductToPostWarehouse()
{
	Menu* postMenu = postModels->initMenu();

	printf("Выберите отделение почты: \n");
	postMenu->draw();

	Post* post = (Post*)Post::selectNeedleModel(postMenu, postModels);
	delete postMenu;

	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	cleanContent();

	Menu* productMenu = productModels->initMenu();
	productMenu->draw();

	Product* product = (Product*)selectNeedleModel(productMenu, productModels);

	delete productMenu;

	PostWarehouse* newPostWarehouse = new PostWarehouse();
	newPostWarehouse->post = post;
	newPostWarehouse->product = product;

	postWarehouseModels->add(newPostWarehouse);
	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	cleanContent();
}

void Post::savePostToFile()
{
	saveModelToFile("Почтовые отделения.txt");

	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf(" Почтовые отделения сохранены в файл! \n");
}

Post* Post::findPostById(int id)
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);

	Model* posts = list;
	Post* foundPost = NULL;

	if (NULL != posts)
	{
		while (posts)
		{
			Post* post = static_cast<Post*>(posts);
			if (post->id == id)
			{
				return post;
			}
			posts = posts->next;
		}
	}

	return NULL;
}

void Post::deletePost()
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
		Post* post = findPostById(id);

		if (NULL == post)
		{
			cleanContent();
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
			printf("Клиент с ID = %d не найден! Пожалуйста попробуйте еще раз.", id);
			Sleep(3000);
			Post::deletePost();
		}

		ConsoleApi::GotoXY(locationForContent->x, ++i);
		printf("Вы уверенны что хотите удалить клиента: \"%s\" ? (y / n) ?", post->name);

		char resp = getchar();
		if (resp == 'y' || resp == 'Y')
		{
			deleteByIndex(post->id - 1);
			cleanContent();
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
			printf("Клиент был удален.");
			Sleep(3000);
			Post::deletePost();
		}

		Post::deletePost();
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
				Post::deletePost();
			}
		}

	}

	free(tempString);
}

Post::~Post() {
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