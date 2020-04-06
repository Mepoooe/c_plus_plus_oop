#ifndef CONSOLE_API_MODULE
#define CONSOLE_API_MODULE

#include <iostream>

class ConsoleApi
{
public:
	enum ConsoleColors {       // LRGB LRGB    Light Reg Green Blue 
		clBlack = 0          // 0000 0000
		, clBlue = 1           // 0000 0001
		, clGreen = 2          // 0000 0010
		, clCyan = 3           // 0000 0011
		, clRed = 4            // 0000 0100
		, clMagenta = 5        // 0000 0101
		, clBrown = 6          // 0000 0110
		, clLightGrey = 7      // 0000 0111
		, clDarkGrey = 8       // 0000 1000 
		, clLightBlue = 9      // 0000 1001
		, clLightGreen = 10    // 0000 1010
		, clLightCyan = 11     // 0000 1011
		, clLightRed = 12      // 0000 1100
		, clLightMagenta = 13  // 0000 1101
		, clYellow = 14        // 0000 1110
		, clWhite = 15         // 0000 1111
	};
	static const int keyEscape = 27;
	static const int keySpace = 32;
	static const int keyBackspace = 8;
	static const int keyTab = 9;
	static const int keyEnter = 13;

	static const int keyInsert = 82;
	static const int keyDelete = 83;

	static const int keyUp = 72;
	static const int keyDown = 80;
	static const int keyLeft = 75;
	static const int keyRight = 77;
	static const int keyPageUp = 73;
	static const int keyPageDown = 81;
	static const int keyHome = 71;
	static const int keyEnd = 79;
	static const int keyCenter = 76;

	static const int keyF1 = 59;
	static const int keyF2 = 60;
	static const int keyF3 = 61;
	static const int keyF4 = 62;
	static const int keyF5 = 63;
	static const int keyF6 = 64;
	static const int keyF7 = 65;
	static const int keyF8 = 66;
	static const int keyF9 = 67;
	static const int keyF10 = 68;
	static const int keyF11 = 69;
	static const int keyF12 = 70;

	static void SetColors(ConsoleColors textColor, ConsoleColors backgroundColor);
	static short X();
	static short Y();
	static void GotoXY(const short x, const short y);
	static void GotoX(const short x);
	static void GotoY(const short y);
	static short Height();
	static short Width();
	static short BufferHeight();
	static short BufferWidth();

	static int KeyPressed();
	static void cls(int it);
};

#endif