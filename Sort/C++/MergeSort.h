#pragma once
#include <vector>

using namespace std;


class MergeSort
{
private:

	vector<int> sTempVector;
	void VectorSort(vector<int>::iterator begin, vector<int>::iterator end);

	int* sTempArray;
	int sTempArraySize;
	void ArraySort(int* begin, int* end);

public:
	void Sort(int* begin, int* end)
	{
		if (sTempArraySize < end - begin)
		{
			delete[] sTempArray;
			sTempArraySize = end - begin;
			sTempArray = new int[sTempArraySize / sizeof(int)];
		}

		ArraySort(begin, end - 1);
	}

	void Sort(vector<int>::iterator begin, vector<int>::iterator end)
	{
		sTempVector.reserve(distance(begin, end));
		VectorSort(begin, end - 1);
	}
};
