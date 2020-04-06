#include "StringHelper.h"

void StringHelper::strNull(char* str, int len) {
	for (int i = 0; i < len; i++)
	{
		*(str + i) = 0;
	}
}

bool StringHelper::strIsNumeric(char* str, int len) {
	bool checked = true;

	int i = 0;
	do
	{
		//valid digit?
		if (isdigit(str[i]))
		{
			//to the next character
			i++;
			checked = true;
		}
		else
		{
			//to the next character
			i++;
			checked = false;
			break;
		}
	} while (str[i] != '\0');

	return checked;
}

void StringHelper::strInput(char* str, int len) {
	int i = 0;
	while (i < (len - 1))
	{
		*(str + i) = getchar();
		if (*(str + i) == '\n')
		{
			break;
		}
		i++;
	}
	*(str + i) = 0;
}

// скрыть/показать текстовый курсор в консоли
void StringHelper::showCursor(bool visible)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ccInfo;
	ccInfo.bVisible = visible;
	ccInfo.dwSize = 20;
	SetConsoleCursorInfo(hStdOut, &ccInfo);
}