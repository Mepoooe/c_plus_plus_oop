#ifndef ORDER_MODULE
#define ORDER_MODULE

#include "Product.h"
#include "Client.h"
#include "Utils.h"
#include "Model.h"

class Order :
	public Model
{
public:
	int id;
	Client* client;
	Product* product;

	void addNewOrder(Client* clientItem, Product* productItem);
	void showAllOrders();
	void run();
	Order();
	~Order();
};
#endif

