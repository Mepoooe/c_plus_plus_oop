#include "Map.h"
#include "GlobalVars.h"

const int n = 90; // horizontal size of the map
const int m = 75; // vertical size size of the map
static int map[n][m];
static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
static int dir_map[n][m]; // map of directions
static int dx[Map::dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[Map::dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

bool operator<(const Node& a, const Node& b)
{
	return a.priority > b.priority;
}

Map::Map() {
	// create empty map
	for (int y = 0; y < m; y++)
	{
		for (int x = 0; x < n; x++) map[x][y] = 0;
	}

	// fillout the map matrix with a '+' pattern
	for (int x = n / 8; x < n * 7 / 8; x++)
	{
		map[x][m / 2] = 1;
	}
	for (int y = m / 8; y < m * 7 / 8; y++)
	{
		map[n / 2][y] = 1;
	}
}

Client* Map::chooseClient() {
	Menu* clientMenu = clientModels->initMenu();

	printf("Выберите клиента: \n");
	clientMenu->draw();

	Client* client = (Client*)Model::selectNeedleModel(clientMenu, clientModels);
	delete clientMenu;
	return client;
}

Post* Map::choosePost() {
	Menu* postMenu = postModels->initMenu();

	printf("Выберите почтовое отделение: \n");
	postMenu->draw();

	Post* post = (Post*)Model::selectNeedleModel(postMenu, postModels);
	delete postMenu;
	return post;
}

void Map::run() {
	Client* needleClient = chooseClient();
	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	needleClient->cleanContent();

	Post* needlePost = choosePost();
	ConsoleApi::SetColors(ConsoleApi::clWhite, ConsoleApi::clBlue);
	needleClient->cleanContent();

	srand(time(NULL));

	// randomly select start and finish locations
	int xA = needleClient->location->x;
	int yA = needleClient->location->y;
	int xB = needlePost->location->x;
	int yB = needlePost->location->y;
	/*switch (rand() % 8)
	{
	case 0: xA = 0; yA = 0; xB = n - 1; yB = m - 1; break;
	case 1: xA = 0; yA = m - 1; xB = n - 1; yB = 0; break;
	case 2: xA = n / 2 - 1; yA = m / 2 - 1; xB = n / 2 + 1; yB = m / 2 + 1; break;
	case 3: xA = n / 2 - 1; yA = m / 2 + 1; xB = n / 2 + 1; yB = m / 2 - 1; break;
	case 4: xA = n / 2 - 1; yA = 0; xB = n / 2 + 1; yB = m - 1; break;
	case 5: xA = n / 2 + 1; yA = m - 1; xB = n / 2 - 1; yB = 0; break;
	case 6: xA = 0; yA = m / 2 - 1; xB = n - 1; yB = m / 2 + 1; break;
	case 7: xA = n - 1; yA = m / 2 + 1; xB = 0; yB = m / 2 - 1; break;
	}*/

	//// get the route
	clock_t start = clock();
	string route = pathFind(xA, yA, xB, yB);

	// follow the route on the map and display it 
	if (route.length() > 0)
	{
		int j; char c;
		int x = xA;
		int y = yA;
		map[x][y] = 2;
		for (int i = 0; i < route.length(); i++)
		{
			c = route.at(i);
			j = atoi(&c);
			x = x + dx[j];
			y = y + dy[j];
			map[x][y] = 3;
		}
		map[x][y] = 4;

		int mapCoordY = 3;
		int mapCoordX = 0;
		// display the map with the route
		for (int y = 0; y < m; y++)
		{
			mapCoordY++;
			mapCoordX = 25;
			for (int x = 0; x < n; x++) {
				ConsoleApi::GotoXY(mapCoordX++, mapCoordY);
				if (map[x][y] == 0)
					printf(".");
				else if (map[x][y] == 1)
					printf("O"); //obstacle
				else if (map[x][y] == 2)
					printf("S"); //start
				else if (map[x][y] == 3)
					printf("R"); //route
				else if (map[x][y] == 4)
					printf("F"); //finish
			}
		}
	}
}

string Map::pathFind(const int& xStart, const int& yStart,
	const int& xFinish, const int& yFinish)
{
	static priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static Node* n0;
	static Node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the Node maps
	for (y = 0; y < m; y++)
	{
		for (x = 0; x < n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// create the start Node and push into list of open nodes
	n0 = new Node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[x][y] = n0->priority; // mark it on the open nodes map

	// A* search
	while (!pq[pqi].empty())
	{
		// get the current Node w/ the highest priority
		// from the list of open nodes
		n0 = new Node(pq[pqi].top().xPos, pq[pqi].top().yPos,
			pq[pqi].top().level, pq[pqi].top().priority);

		x = n0->xPos; y = n0->yPos;

		pq[pqi].pop(); // remove the Node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + Map::dir / 2) % Map::dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i < Map::dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child Node
				m0 = new Node(xdx, ydy, n0->level,
					n0->priority);
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->priority;
					pq[pqi].push(*m0);
					// mark its parent Node direction
					dir_map[xdx][ydy] = (i + Map::dir / 2) % Map::dir;
				}
				else if (open_nodes_map[xdx][ydy] > m0->priority)
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->priority;
					// update the parent direction info
					dir_map[xdx][ydy] = (i + Map::dir / 2) % Map::dir;

					// replace the Node
					// by emptying one pq to the other one
					// except the Node to be replaced will be ignored
					// and the new Node will be pushed in instead
					while (!(pq[pqi].top().xPos == xdx &&
						pq[pqi].top().yPos == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted Node

					// empty the larger size pq to the smaller one
					if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better Node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return ""; // no route found
}