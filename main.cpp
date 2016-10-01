
#include <algorithm>
#include <cstdlib>
#include <climits>
#include "Utility.h"
#define CONTAINER_LIMIT 100
#define WEIGHT_COUNT 20
#define STACK_SIZE 3

using namespace std;




int main() {
	
	vector<Container> containers(1);
	Weight weights [STACK_SIZE][WEIGHT_COUNT];
	readFromStream("inputs.txt", weights, WEIGHT_COUNT);

	for (size_t i = 0; i < STACK_SIZE; i++)
	{
		outStream << "Stack #" << i + 1 << endl;
		GoF(weights[i], containers, WEIGHT_COUNT);
	}

	SORTCOUNT = int(WEIGHT_COUNT * log10(WEIGHT_COUNT));
	for (size_t i = 0; i < STACK_SIZE; i++)
	{
		sort(begin(weights[i]), end(weights[i]));
		outStream << "Sorted Stack #" << i << endl;
		GoF(weights[i], containers, WEIGHT_COUNT);
	}
	Weight topStack[STACK_SIZE * WEIGHT_COUNT];
	SORTCOUNT = 0.0;
	for (size_t i = 0; i < STACK_SIZE; i++)
		for (size_t j = 0; j < WEIGHT_COUNT; j++)
			{
				topStack[i * WEIGHT_COUNT + j].weight = weights[i][j].weight;
			}
	outStream << "Main Stack #" << endl;
	GoF(topStack, containers, STACK_SIZE * WEIGHT_COUNT);

	sort(begin(topStack), end(topStack));
	SORTCOUNT = 60 * log10(60);
	outStream << "Sorted Main Stack #" << endl;
	GoF(topStack, containers, STACK_SIZE * WEIGHT_COUNT);

	system("pause");
}



