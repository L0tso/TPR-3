#pragma once
class Weight {
public:
	int weight;
	int index;
	bool operator < (const Weight secondPoint);
};