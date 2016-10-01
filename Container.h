#pragma once
#include <vector>
#include "Weight.h"

#define CONTAINER_LIMIT 100

using namespace std;
class Container
{
public:
	Container();
	int weight = 0;
	int index;
	static int count;
	vector<int> indexs;
	bool addItem(Weight item);
	bool Container::operator < (const Container secondPoint)
	{
		return(secondPoint.weight < this->weight);
	}

	virtual ~Container();
};

