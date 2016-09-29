#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <climits>
#define CONTAINER_LIMIT 100
#define WEIGHT_COUNT 15

using namespace std;
class Weight {
	public:
		int weight;
		int index;
};


class Container
{
public:
	int weight = 0;
	vector<int> indexs;
	bool addItem(Weight item);
	static int count;
	int index;
	Container();
	bool Container::operator < (const Container secondPoint)
	{
		return(secondPoint.weight < this->weight);
	}

};
int Container::count = 1;


Container::Container()
{
	index = count;
	count++;
	
};




void NFA(Weight *weights, vector<Container> &containers) {
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))
		{
			i++;
		}
		else
		{
			
			containers.push_back(Container());
			containers.back().addItem(weights[i]);
			i++;

		}

	}
	for (size_t i = 0; i < containers.size(); i++)
	{
		cout << "Container " << i+1 << " :  ";
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout<<containers[i].indexs[j] << "  ";
		}
		cout << endl;
	}


	/*for (size_t i = 0; i < containers.size(); i++)
	{
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout << containers[i].indexs[j] << "  ";
		}
	}cout << endl;*/


}


/* i ітератор по товарам
   j ітератор по контейнерам
*/
void FFA(Weight *weights, vector<Container> &containers) {
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))	i++;		//якщо є місце в поточному контейнері додаємо та переходимо до іншого
		else
		{
			bool flag = false;										//Флаг що показує чи додано товар до вже існуючих контейнерів
			int j = 0;
			while ( j < containers.size() - 1)						//перевіряємо чи влазить товар, у інші, уже створені контейнери
			{

				if (flag == false) {
					if(!containers.back().addItem(weights[i]));		   //Перевірка останнього 
						flag = containers[j].addItem(weights[i]);	
				}			
				j++;													//перехід до іншого контейнера без створення
			}
			if (flag) {													
				i++;													//перехід до іншого товару
			}
			else
			{
				containers.push_back(Container());						//створення контейнеру та додавання товару
				containers.back().addItem(weights[i]);
				i++;
			}
			
		}

	}
	for (size_t i = 0; i < containers.size(); i++)
	{
		cout << "Container " << i + 1 << " :  ";
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout << containers[i].indexs[j] << "  ";
		}
		cout << endl;
	}

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
void WFA(Weight *weights, vector<Container> &containers) {
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))	i++;		
		else
		{
			if ( containers[findMax(containers)].addItem(weights[i])) i++;
			else {
				containers.push_back(Container());						
				containers.back().addItem(weights[i]);
				i++;
			}
		}
	}

	for (size_t i = 0; i < containers.size(); i++)
	{
		cout << "Container " << i + 1 << " :  ";
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout << containers[i].indexs[j] << "  ";
		}
		cout << endl;
	}
}

void BFA(Weight *weights, vector<Container> containers) {
	bool flag = false;
	int j = 0;
	
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))	i++;
		else {
			sort(containers.begin(), containers.end());
			while (j < containers.size() - 1)						//перевіряємо чи влазить товар, у інші, уже створені контейнери
			{
				
				if (flag == false) {
					flag = containers[j].addItem(weights[i]);
				}
				j++;													//перехід до іншого контейнера без створення
			}
			if (flag) {
				i++;													//перехід до іншого товару
			}
			else
			{
				containers.push_back(Container());						//створення контейнеру та додавання товару
				containers.back().addItem(weights[i]);
				i++;
			}
			}
			
		}
	for (size_t i = 0; i < containers.size(); i++)
	{
		cout << "Container " << containers[i].index << " :  ";
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout << containers[i].indexs[j] << "  ";
		}
		cout << endl;
	}
	
}
int main() {
	ifstream inputFileStream("inputs.txt");

	Weight* weights = new Weight[WEIGHT_COUNT];
	int i = 0;
	while (!inputFileStream.eof())
	{
		
		inputFileStream >> weights[i].weight;
		weights[i].index = i+1;
		i++;
	}
	for (size_t i = 0; i < WEIGHT_COUNT; i++)
	{
		cout << weights[i].weight << "  " << weights[i].index << endl;
	}
	
	vector<Container> containers;
	containers.resize(1);

	
	//FFA(weights, containers);
	//WFA(weights, containers);
	
	BFA(weights, containers);
	system("pause");
}

bool Container::addItem(Weight item)
{
	if(weight + item.weight >CONTAINER_LIMIT)
		{
			return false;
		}	
	else {
		weight += item.weight;
		indexs.push_back(item.index);
		return true;
	}
}


