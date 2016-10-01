#include "Container.h"

int Container::count = 1;
Container::Container()
{
	index = count;
	count++;
};

bool Container::addItem(Weight item)
{
	if (weight + item.weight >CONTAINER_LIMIT)
	{
		return false;
	}
	else {
		weight += item.weight;
		indexs.push_back(item.index);
		return true;
	}
}

bool Container::operator<(const Container secondPoint)
{
	return(secondPoint.weight < this->weight);
}



Container::~Container()
{
}
