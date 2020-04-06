#ifndef PRODUCT_MODULE
#define PRODUCT_MODULE

#include "Model.h"
class Product :
	public Model
{
private:
	typedef struct {
		int id;
		const char* str;
		short x;
		short y;
	} itemClientMenu;

	enum menuItems { MENU_BACK, MENU_SHOW, MENU_ADD, MENU_DELETE, MENU_SAVE_TO_FILE };

	itemClientMenu menuItemsList[MENU_SAVE_TO_FILE + 1] = {
		{ MENU_BACK, " Назад ", 2, 3},
		{ MENU_SHOW, " Показать список ", 2, 4},
		{ MENU_ADD, " Добавить ", 2, 5},
		{ MENU_DELETE, " Удалить ", 2, 6},
		{ MENU_SAVE_TO_FILE, " Сохранить в файл ", 2, 7}
	};
	
public:
	int id;
	char* name = NULL;
	char* description = NULL;
	float price;

	Product();

	virtual void run();
	virtual void fillMenuItem(Menu* newMenu, Model* item, int x, int y);
	void addNewProduct();
	void showAllProducts();
	void deleteProduct();
	void saveProductToFile();

	virtual void printToFile(FILE* fileHandle, Model* item);

	Product* findProductById(int id);

	~Product();
};

#endif