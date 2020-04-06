#include "MenuItem.h"

MenuItem::MenuItem()
{
	id = 0;
	caption = (char*)malloc(captionLength * sizeof(char));

	StringHelper::strNull(caption, captionLength);
}

void MenuItem::setPosition(short x, short y)
{
	position = new Location(x, y);
}

MenuItem::~MenuItem()
{
	free(caption);

	if (NULL != position)
	{
		delete position;
	}
}