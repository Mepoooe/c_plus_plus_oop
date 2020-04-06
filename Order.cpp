#include "Order.h"


void Order::addNewOrder(Client* clientItem, Product* productItem)
{
	Order* newOrder = new Order();

	newOrder->id = getLastIndex();
	newOrder->client = clientItem;
	newOrder->product = productItem;

	add(newOrder);
}

void Order::showAllOrders()
{
	ConsoleApi::GotoXY(locationForContent->x, locationForContent->y);
	printf("Order List! \n");

	Order* Orders = (Order*)list;
	int i = 2;
	if (NULL == Orders)
	{
		ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
		printf("List of Orders is empty!");
	}
	else {
		while (NULL != Orders)
		{
			ConsoleApi::GotoXY(locationForContent->x, locationForContent->y + i);
			printf("ID: %d; Name: %s; Product: %s;\n", Orders->id, Orders->client->name, Orders->product->name);
			Orders = (Order*)Orders->next;
			i++;
		}
	}
}

void Order::run()
{
	
}

Order::Order()
{
	
}

Order::~Order()
{
	
}