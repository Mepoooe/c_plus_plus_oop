#ifndef STRING_HELPER_MODULE
#define STRING_HELPER_MODULE

#include <conio.h> 
#include <iostream>
#include <windows.h>

class StringHelper
{
public:
	static void strNull(char* str, int len);
	static void strInput(char* str, int len);
	static bool strIsNumeric(char* str, int len);
	static void showCursor(bool visible);
};

#endif