#include <iostream>
#include <fstream>
#include "Container.h"
#include <algorithm>
#include <cstdlib>
#include <climits>
#define CONTAINER_LIMIT 100
#define WEIGHT_COUNT 20
#define STACK_SIZE 3

using namespace std;
int SORTCOUNT;
void printOut(char* str, vector<Container> containers, int count )
{
	cout << str <<  "Count:   " << count << endl;
	/*for (size_t i = 0; i < containers.size(); i++)
	{
		cout << "Container " << i + 1 << " :  ";
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout << containers[i].indexs[j] << "  ";
		}
		cout << endl;
	}*/
	
}

void NFA(Weight *weights, vector<Container> containers) {
	int globalCount = 0;
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i])) 
		{	
			i++;
			globalCount++;
		}
		else
		{
			containers.push_back(Container());
			containers.back().addItem(weights[i]);
			globalCount++;

			i++;
		}
	}
	printOut("NFA", containers, globalCount);

}


/* i ітератор по товарам
   j ітератор по контейнерам
*/
void FFA(Weight *weights, vector<Container> containers) {

	int globalCount = 0;
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))
		{
			i++;													//якщо є місце в поточному контейнері додаємо та переходимо до іншого
			globalCount++;
		}							
		else
		{
			bool flag = false;										//Флаг що показує чи додано товар до вже існуючих контейнерів
			int j = 0;
			while ( j < containers.size() - 1)						//перевіряємо чи влазить товар, у інші, уже створені контейнери
			{

				if (flag == false) {
					globalCount++;
					if(!containers.back().addItem(weights[i]));		   //Перевірка останнього 
						flag = containers[j].addItem(weights[i]);	
				}			
				j++;													//перехід до іншого контейнера без створення
			}
			if (flag) i++; 																//перехід до іншого товару		
			else
			{
				containers.push_back(Container());						//створення контейнеру та додавання товару
				containers.back().addItem(weights[i]);
				i++;
			}
			
		}

	}
	printOut("FFA", containers, globalCount);

}
int findMax(vector<Container> containers) {
	int minimum = INT_MAX;
	int index = 0;
	for (size_t i = 0; i < containers.size(); i++)
	{
		if (containers[i].weight < minimum)
		{
			minimum = containers[i].weight;
			index = i;
		}
	}
	return index;

}
void WFA(Weight *weights, vector<Container> containers) {
	int globalCount = 0;
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))
		{
			i++;
			globalCount++;
		}
		else
		{
			if (containers[findMax(containers)].addItem(weights[i]))
			{
				i++;
				globalCount += containers.size();
			}
			else {
				globalCount += containers.size();
				containers.push_back(Container());						
				containers.back().addItem(weights[i]);
				i++;
			}
		}
	}
	printOut("WFA",containers, globalCount);
}
void BFA(Weight *weights, vector<Container> containers) {
	int globalCount = 0;
	bool flag = false;
	int j = 0;
	
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))
		{
			i++;
			globalCount++;
		}
		else {
			bool flag = false;
			sort(containers.begin(), containers.end());
			globalCount += containers.size();
			while (j < containers.size() - 1)						//перевіряємо чи влазить товар, у інші, уже створені контейнери
			{
				
				if (flag == false) {
					flag = containers[j].addItem(weights[i]);
					globalCount++;
				}
				j++;													//перехід до іншого контейнера без створення
			}
			if (flag)
			{
				i++;													//перехід до іншого товару
				globalCount++;
			}									
			else
			{
				globalCount++;
				containers.push_back(Container());						//створення контейнеру та додавання товару
				containers.back().addItem(weights[i]);
				i++;
			}
			}
			
		}
	printOut("BFA",containers, globalCount);
	
}
int main() {
	ifstream inputFileStream("inputs.txt");

	Weight weights [STACK_SIZE][WEIGHT_COUNT];
	int i = 0; int j=0;
	while (!inputFileStream.eof())
	{	
		inputFileStream >> weights[i][j].weight;
		weights[i][j].index = j+1;
		j++;
		if(j == 20)
		{
			i++;
			j = 0;
		}
		
	}
	inputFileStream.close();
	for (size_t i = 0 ; i < STACK_SIZE; i++)
	for (size_t j = 0; j < WEIGHT_COUNT; j++)
	{
		cout << weights[i][j].weight << "  " << weights[i][j].index << endl;
	}
	vector<Container> containers(1);
	for (size_t i = 0; i < STACK_SIZE; i++)
	{
		NFA(weights[i], containers);
		FFA(weights[i], containers);
		WFA(weights[i], containers);
		BFA(weights[i], containers);
	}
	for (size_t i = 0; i < STACK_SIZE; i++)
	{

	}

	system("pause");
}



