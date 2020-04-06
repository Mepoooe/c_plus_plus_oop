#include "Desktop.h"

Desktop::Desktop() {
	setlocale(LC_CTYPE, "rus");
	SetConsoleTitle(L"�������� ����");

	renderConsoleBackground();
	setScreenBufferSize();

	mainMenu = new MainMenu();
}

void Desktop::render() {
	mainMenu->drawMenu();
}

void Desktop::renderConsoleBackground() {
	HANDLE hStdOut; //���������� ����������� ����
	WORD wo�kWindowAttributes = 158;//�������� ������� �������

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	system("CLS");
}

void Desktop::setScreenBufferSize() {
	const int col = 150; // ������ ���� �������
	const int row = 80; // ������ �������
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Console Mouse Demo");
	// --- 1. ������ ������ ������� � ��� ����������� ������ ---
	SMALL_RECT windowSize = { 0,0,col - 1,row - 1 };
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	COORD bufferSize = { col,row }; // ������� ����������� ������
	// ��������� ������� ����������� ������ ���� �������
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}

Desktop::~Desktop() {
	delete mainMenu;
}