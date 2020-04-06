#include "Menu.h"

Menu::Menu() {
	countItem = 0;

	for (int i = 0; i < maxItems; i++)
	{
		items[i] = NULL;
	}
}

int Menu::addItem(const char *caption, short x, short y, ConsoleApi::ConsoleColors textColor, ConsoleApi::ConsoleColors backgroundColor)
{
	items[countItem] = new MenuItem();

	items[countItem]->id = countItem;
	items[countItem]->setPosition(x, y);
	items[countItem]->textColor = textColor;
	items[countItem]->backgroundColor = backgroundColor;
	strcpy_s(items[countItem]->caption, MenuItem::captionLength, caption);
	countItem++;
	return countItem;
}

int Menu::maxCaptionLength()
{
	int result = 0;

	for (int i = 0; i < countItem; i++)
	{
		if (strlen(items[i]->caption) > result)
		{
			result = strlen(items[i]->caption);
		}
	}

	return result;
}

int Menu::getCountItem()
{
	return countItem;
}

void Menu::clear()
{
	for (int i = (countItem - 1); i >= 0; i--)
	{
		delete items[i];
		items[i] = NULL;
	}
}

void Menu::setPosition(short x, short y)
{
	position = new Location(x, y);
}

void Menu::setSelectedItemById(int id) {
	for (int i = 0; i < countItem; i++)
	{
		ConsoleApi::GotoXY(items[i]->position->x, (items[i]->position->y));

		if (i == id)
		{
			selected = id;
			ConsoleApi::SetColors(selectedTextColor, selectedBackgroundColor);
		}
		else {
			ConsoleApi::SetColors(items[i]->textColor, items[i]->backgroundColor);
		}

		for (int j = 0; j < maxCaptionLength(); j++)
		{
			if (j > strlen(items[i]->caption))
			{
				printf(" ");
			}
			else {
				printf("%c", items[i]->caption[j]);
			}
		}
	}
}

void Menu::draw()
{
	for (int i = 0; i < countItem; i++)
	{
		ConsoleApi::GotoXY(items[i]->position->x, (items[i]->position->y));

		if (i == selected)
		{
			ConsoleApi::SetColors(selectedTextColor, selectedBackgroundColor);
		}
		else {
			ConsoleApi::SetColors(items[i]->textColor, items[i]->backgroundColor);
		}

		for (int j = 0; j < maxCaptionLength(); j++)
		{
			if (j > strlen(items[i]->caption))
			{
				printf(" ");
			}
			else {
				printf("%c", items[i]->caption[j]);
			}
		}
	}
}

Menu::~Menu() {
	for (int i = (countItem - 1); i >= 0; i--)
	{
		if (NULL != items[i])
		{
			delete items[i];
		}
	}

	if (NULL != position)
	{
		delete position;
	}
}