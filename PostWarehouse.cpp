#include "PostWarehouse.h"


void PostWarehouse::addNewPostWarehouse(Post* postItem, Product* productItem)
{
	PostWarehouse* newPostWarehouse = new PostWarehouse();

	newPostWarehouse->id = getLastIndex();
	newPostWarehouse->post = postItem;
	newPostWarehouse->product = productItem;

	add(newPostWarehouse);
}

void PostWarehouse::showAllPostWarehouses()
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf("PostWarehouse List! \n");

	PostWarehouse* PostWarehouses = (PostWarehouse*)list;
	int i = 2;
	if (NULL == PostWarehouses)
	{
		ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
		printf("List of PostWarehouses is empty!");
	}
	else {
		while (NULL != PostWarehouses)
		{
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
			printf("ID: %d; Name: %s; Product: %s;\n", PostWarehouses->id, PostWarehouses->post->name, PostWarehouses->product->name);
			PostWarehouses = (PostWarehouse*)PostWarehouses->next;
			i++;
		}
	}
}

void PostWarehouse::run()
{

}

PostWarehouse::PostWarehouse()
{

}

PostWarehouse::~PostWarehouse()
{

}