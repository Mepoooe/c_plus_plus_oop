#ifndef POST_WAREHOUSE_MODULE
#define POST_WAREHOUSE_MODULE

#include "Product.h"
#include "Utils.h"
#include "Post.h"
#include "Model.h"

class PostWarehouse:
	public Model
{
public:
	int id;
	Post* post;
	Product* product;

	void addNewPostWarehouse(Post* postItem, Product* productItem);
	void showAllPostWarehouses();
	void run();
	PostWarehouse();
	~PostWarehouse();
};


#endif // !POST_WAREHOUSE_MODULE


