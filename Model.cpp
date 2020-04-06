#include "Model.h"
#include "MainMenu.h"
#include "Environment.h"
#include "StringHelper.h"
#include "Directory.h"

Model::Model() {
	list = NULL;
	locationForContent = new Location(25, 3);
	maxLocationForContent = new Location(80, 80);

	initFolderStore();
}

void Model::initFolderStore() {
	folderDataStore = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(folderDataStore, stringLength);
	// 2.1. определить стандартные пути MyDocuments\MyApplication
	if (0 == Environment::GetFolderPath(Environment::MyDocuments, folderDataStore)) {
		Environment::setCurrentDirectory(folderDataStore);
		if (!Directory::Exists(CFolderStore)) {
			Directory::CreateDir(CFolderStore);
		}
		Directory::Combine(folderDataStore, CFolderStore);
		Environment::setCurrentDirectory(folderDataStore);
	}
	else {
		printf("Error %d. Не удлалось получить путь к каталогу \"Мои Документы\"! \n", ApplicationErrorCannotGetMyDocumenst);
	}
}

void Model::fillMenuItem(Menu* newMenu, Model *item, int x, int y) {

}

Menu* Model::initMenu() {
	Menu* newMenu = new Menu();
	Model* item = getFirst();
	int x = locationForContent->x;
	int y = locationForContent->y;

	ConsoleApi::GotoXY(x, y);

	y += 2;

	for (int i = 0; i < Menu::maxItems; i++)
	{
		if (NULL != item)
		{
			fillMenuItem(newMenu, item, x, y++);
			item = item->next;
		}
		else {
			break;
		}

	}

	return newMenu;
}

Model* Model::selectNeedleModel(Menu *currentMenu, Model *models) {

	int iKey = 0;
	bool notExit = true;
	Model* needleModel = NULL;

	while (notExit)
	{
		if (_kbhit())
		{
			iKey = _getch();
			switch (iKey)
			{
			case ConsoleApi::keyDown:
				if (currentMenu->selected < currentMenu->countItem - 1) {
					currentMenu->setSelectedItemById(currentMenu->selected + 1);
				}
				else {
					currentMenu->setSelectedItemById(0);
				}
				StringHelper::showCursor(false);
				break;
			case ConsoleApi::keyUp:
				if (currentMenu->selected > 0) {
					currentMenu->setSelectedItemById(currentMenu->selected - 1);
				}
				else {
					currentMenu->setSelectedItemById(currentMenu->countItem - 1);
				}
				StringHelper::showCursor(false);
				break;
			case ConsoleApi::keyEnter:
				StringHelper::showCursor(true);

				needleModel = models->getModelByIndex(currentMenu->selected);
				notExit = false;
				break;
			case ConsoleApi::keyEscape: // выход по клавише ESC
				notExit = false;
			}
		}
	}

	return needleModel;
}

void Model::run() {

}

void Model::cleanContent() {
	char fill = ' ';
	COORD tl = { locationForContent->x, locationForContent->y };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);


	menu->setSelectedItemById(menu->selected);
	MainMenu::renderBorders();
	ConsoleApi::GotoXY(0, 0);
}

int Model::getCount()
{
	Model* firstItem = getFirst();
	int result = 0;

	while (NULL != firstItem)
	{
		result++;
		firstItem = firstItem->next;
	}

	return result;
}

int Model::getLastIndex()
{
	return getCount() + 1;
}

Model* Model::getLast()
{
	Model* result = list;

	while (NULL != result)
	{
		if (NULL != result->next)
		{
			result = result->next;
		}
		else {
			break;
		}
	}

	return result;
}

Model* Model::getFirst()
{
	Model* result = list;

	while (NULL != result)
	{
		if (NULL != result->prev)
		{
			result = result->prev;
		}
		else {
			break;
		}

	}

	return result;
}

void Model::deleteByIndex(int index)
{
	Model* itemForDelete = getModelByIndex(index);
	bool isOne = getCount() == 1;

	if (NULL != itemForDelete)
	{
		Model* lpred, * lnext;
		lnext = itemForDelete->next;
		lpred = itemForDelete->prev;

		if (NULL != lnext)
		{
			lnext->prev = itemForDelete->prev;
		}
		if (NULL != lpred)
		{
			lpred->next = itemForDelete->next;
		}
		delete itemForDelete;
	}
	if (isOne)
	{
		list = NULL;
	}
}

void Model::deleteAll()
{
	Model* item = getLast();

	while (NULL != item)
	{
		Model* itemForDelete = item;
		item = item->prev;
		delete itemForDelete;
	}
	list = NULL;
}

void Model::add(Model* people)
{
	int newIndex = getCount() - 1;
	newIndex = newIndex < 0 ? 0 : newIndex;

	insert(newIndex, people);
}

Model* Model::insert(int index, Model* model)
{
	Model* prevModel = getModelByIndex(index);
	//Model* result = model;

	model->prev = prevModel;
	if (NULL != prevModel)
	{
		model->next = prevModel->next;
		if (NULL != prevModel->next) {
			prevModel->next->prev = model;
		}
		prevModel->next = model;
	}
	else {
		list = model;
	}

	return model;
}

Model* Model::getModelByIndex(int index)
{
	Model* result = NULL;

	if (index >= 0 && index < getCount())
	{
		int i = 0;
		result = getFirst();

		while (i != index && NULL != result)
		{
			result = result->next;
			i++;
		}
	}

	return result;
}

void Model::printToFile(FILE* fileHandle, Model* item) {

}

void Model::saveModelToFile(const char* fileName) {

	char* fileDestination = (char*)malloc(stringLength * sizeof(char));
	StringHelper::strNull(fileDestination, stringLength);
	strcpy_s(fileDestination, stringLength, folderDataStore);
	Directory::Combine(fileDestination, fileName);

	FILE* fileToSave;
	Model* firstModel = getFirst();
	int err = fopen_s(&fileToSave, fileDestination, "w+");

	if (0 == err) {
		while (NULL != firstModel) {
			printToFile(fileToSave, firstModel);
			firstModel = firstModel->next;
		}
		fclose(fileToSave);
	}
}


Model::~Model() {
	deleteAll();

	if (NULL != locationForContent)
	{
		delete locationForContent;
	}

	if (NULL != maxLocationForContent)
	{
		delete maxLocationForContent;
	}

	free(folderDataStore);
}