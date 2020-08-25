#pragma once
#include <vector>

using namespace std;


class MergeSort
{
private:

	static vector<int> sTempVector;
	static void VectorSort(vector<int>::iterator begin, vector<int>::iterator end);

	static int* sTempArray;
	static int sTempArraySize;
	static void ArraySort(int* begin, int* end);

public:
	static void Sort(int* begin, int* end)
	{
		if (sTempArraySize < end - begin)
		{
			delete[] sTempArray;
			sTempArraySize = end - begin;
			sTempArray = new int[sTempArraySize / sizeof(int)];
		}

		ArraySort(begin, end - 1);
	}

	static void Sort(vector<int>::iterator begin, vector<int>::iterator end)
	{
		sTempVector.reserve(distance(begin, end));
		VectorSort(begin, end - 1);
	}


};




