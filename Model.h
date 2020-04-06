#ifndef MODEL_MODULE
#define MODEL_MODULE

#include "Menu.h"
#include "Location.h"

class Model
{
public:
	const int stringLength = 255;

	const char* CFolderStore = "MyApplication\0";
	const char* CFileClients = "Clients.txt\0";
	const char* CFileProducts = "Products.txt\0";
	const char* CFilePosts = "Posts.txt\0";

	char* folderDataStore;

	const int ApplicationErrorCannotGetMyDocumenst = 1;

	Model* next;
	Model* prev;
	Model* list;
	Menu* menu;
	Location* locationForContent;
	Location* maxLocationForContent;

	Model();
	int getCount();
	int getLastIndex();
	void initFolderStore();
	void add(Model* model);
	void deleteByIndex(int index);
	void deleteAll();
	void cleanContent();
	void saveModelToFile(const char* fileName);
	virtual void fillMenuItem(Menu* newMenu, Model *item, int x, int y);
	virtual void printToFile(FILE* fileHandle, Model* item);
	Menu* initMenu();
	Model* getFirst();
	static Model* selectNeedleModel(Menu* currentMenu, Model* models);
	Model* getLast();
	Model* getModelByIndex(int index);
	Model* insert(int index, Model* model);
	~Model();

	virtual void run();
};


#endif