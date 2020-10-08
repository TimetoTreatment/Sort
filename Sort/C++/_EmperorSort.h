#pragma once
#include <random>

using namespace std;

class EmperorSort
{
private:

	static random_device mSeed;
	static mt19937 mEngine;

	int FindPivot(int* ar, int start, int end);
	void Swap(int& left, int& right);
	void InsertionSort(int* ar, int start, int end);
	void rSort(int* ar, int start, int end);

public:

	void Sort(int* ar, int size)
	{
		rSort(ar, 0, size - 1);
	}
};

