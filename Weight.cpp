#include "Weight.h"

bool Weight::operator<(const Weight secondPoint)
{
	return secondPoint.weight < this->weight;
}
