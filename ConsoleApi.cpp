#include "ConsoleApi.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

void ConsoleApi::SetColors(ConsoleColors textColor, ConsoleColors backgroundColor) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCons, (WORD)((backgroundColor << 4) | textColor));
};

short ConsoleApi::X() {
	short x = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_SCREEN_BUFFER_INFO scrInfo;
	if (true == GetConsoleScreenBufferInfo(hCons, &scrInfo)) {
		x = scrInfo.dwCursorPosition.X;
	}
	return x;
};

short ConsoleApi::Y() {
	short y = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO*)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		y = scrInfo->dwCursorPosition.Y;
	}
	free(scrInfo);
	return y;
};

void ConsoleApi::GotoXY(const short x, const short y) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hCons, position);
};

void ConsoleApi::GotoX(const short x) {
	GotoXY(x, Y());
};

void ConsoleApi::GotoY(const short y) {
	GotoXY(X(), y);
};

short ConsoleApi::Height() {
	short y = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO*)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		y = scrInfo->dwMaximumWindowSize.Y;
	}
	free(scrInfo);
	return y;
};

short ConsoleApi::Width() {
	short x = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO*)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		x = scrInfo->dwMaximumWindowSize.X;
	}
	free(scrInfo);
	return x;
};

short ConsoleApi::BufferHeight() {
	short y = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO*)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		y = scrInfo->dwSize.Y;
	}
	free(scrInfo);
	return y;
};

short ConsoleApi::BufferWidth() {
	short x = 0;
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO scrInfo = (_CONSOLE_SCREEN_BUFFER_INFO*)malloc(sizeof(struct _CONSOLE_SCREEN_BUFFER_INFO));
	if (true == GetConsoleScreenBufferInfo(hCons, scrInfo)) {
		x = scrInfo->dwSize.X;
	}
	free(scrInfo);
	return x;
};

int ConsoleApi::KeyPressed() {
	return _getch();
};