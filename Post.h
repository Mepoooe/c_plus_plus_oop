#ifndef POST_MODULE
#define POST_MODULE

#include "Model.h"

class Post :
	public Model
{
private:
	typedef struct {
		int id;
		const char* str;
		short x;
		short y;
	} itemPostMenu;

	enum menuItems { MENU_BACK, MENU_SHOW, MENU_ADD_PRODUCT, MENU_ADD, MENU_DELETE, MENU_SAVE_TO_FILE };

	itemPostMenu menuItemsList[MENU_SAVE_TO_FILE + 1] = {
		{ MENU_BACK, " ����� ", 2, 3},
		{ MENU_SHOW, " �������� ������ ", 2, 4},
		{ MENU_ADD_PRODUCT, " �������� �������", 2, 5},
		{ MENU_ADD, " �������� ", 2, 6},
		{ MENU_DELETE, " ������� ", 2, 7},
		{ MENU_SAVE_TO_FILE, " ��������� � ���� ", 2, 8}
	};

public:
	int id;
	char* name;
	char* address;
	int age;
	Location *location;

	Post();

	virtual void run();
	virtual void fillMenuItem(Menu* newMenu, Model* item, int x, int y);
	//void deletePosts();
	void addNewPost();
	void showAllPosts();
	void deletePost();
	void savePostToFile();
	void addProductToPostWarehouse();

	virtual void printToFile(FILE* fileHandle, Model* item);

	Post* findPostById(int id);

	~Post();
};

#endif