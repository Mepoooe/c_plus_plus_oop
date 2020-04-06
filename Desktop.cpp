#include "Desktop.h"

Desktop::Desktop() {
	setlocale(LC_CTYPE, "rus");
	SetConsoleTitle(L"Короткий путь");

	renderConsoleBackground();
	setScreenBufferSize();

	mainMenu = new MainMenu();
}

void Desktop::render() {
	mainMenu->drawMenu();
}

void Desktop::renderConsoleBackground() {
	HANDLE hStdOut; //дескриптор консольного окна
	WORD woкkWindowAttributes = 158;//атрибуты рабочей области

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	system("CLS");
}

void Desktop::setScreenBufferSize() {
	const int col = 150; // ширина окна консоли
	const int row = 80; // высота консоли
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Console Mouse Demo");
	// --- 1. Задаем размер консоли и его внутреннего буфера ---
	SMALL_RECT windowSize = { 0,0,col - 1,row - 1 };
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	COORD bufferSize = { col,row }; // размеры внутреннего буфера
	// Изменение размера внутреннего буфера окна консоли
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}

Desktop::~Desktop() {
	delete mainMenu;
}