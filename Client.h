#ifndef CLIENT_MODULE
#define CLIENT_MODULE

#include "Model.h"
#include "Product.h"
#include "Utils.h"

class Client :
	public Model
{
private:
	typedef struct {
		int id;
		const char* str;
		short x;
		short y;
	} itemClientMenu;

	enum menuItems { MENU_BACK, MENU_SHOW, MENU_ADD, MENU_ADD_PRODUCT, MENU_DELETE, MENU_SAVE_TO_FILE };

	itemClientMenu menuItemsList[MENU_SAVE_TO_FILE + 1] = {
		{ MENU_BACK, " Назад ", 2, 3},
		{ MENU_SHOW, " Показать список ", 2, 4},
		{ MENU_ADD, " Добавить клиента", 2, 5},
		{ MENU_ADD_PRODUCT, " Добавить продукт", 2, 6},
		{ MENU_DELETE, " Удалить ", 2, 7},
		{ MENU_SAVE_TO_FILE, " Сохранить в файл ", 2, 8}
	};

public:
	int id;
	char* name;
	char* address;
	int age;
	Location *location;

	Client();

	virtual void run();
	//void deleteClients();
	void fillMenuItem(Menu* newMenu, Model *item, int x, int y);
	void addNewClient();
	void showAllClients();
	void deleteClient();
	void saveClientToFile();
	void addProductForClient();

	virtual void printToFile(FILE* fileHandle, Model* item);

	Client* findClientById(int id);

	~Client();
};

#endif