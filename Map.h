#ifndef MAP_MODULE
#define MAP_MODULE

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "Node.h"
#include "Client.h"
#include "Post.h"
#include "ConsoleApi.h"

using namespace std;


//bool operator<(const Node& a, const Node& b)
//{
//	return a.priority > b.priority;
//}

class Map
{
public:
	static const int dir = 8;
	int startX;
	int startY;
	int finishX;
	int finishY;

	Map();
	string pathFind(const int& xStart, const int& yStart,
		const int& xFinish, const int& yFinish);
	void run();
	Client* chooseClient();
	Post* choosePost();
};

#endif