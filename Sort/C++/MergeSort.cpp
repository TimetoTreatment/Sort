#include "MergeSort.h"

void MergeSort::ArraySort(int* begin, int* end)
{
	if (begin >= end)
		return;

	int* center = begin + (end - begin) / 2;

	ArraySort(begin, center);
	ArraySort(center + 1, end);

	int* left = begin;
	int* right = center + 1;
	int index;

	sTempVector.clear();

	for (; left <= center && right <= end;)
	{
		if (*left <= *right)
		{
			sTempVector.emplace_back(*left);
			left++;
		}
		else
		{
			sTempVector.emplace_back(*right);
			right++;
		}
	}

	while (left <= center)
	{
		sTempVector.emplace_back(*left);
		left++;
	}

	while (right <= end)
	{
		sTempVector.emplace_back(*right);
		right++;
	}

	index = 0;

	for (auto iter = begin; iter <= end; iter++)
	{
		*iter = sTempVector[index];
		index++;
	}
}


void MergeSort::VectorSort(vector<int>::iterator begin, vector<int>::iterator end)
{
	if (begin >= end)
		return;

	vector<int>::iterator center = begin;
	advance(center, distance(begin, end) / 2);

	VectorSort(begin, center);
	VectorSort(center + 1, end);

	vector<int>::iterator left, right;

	int index;

	left = begin;
	right = center + 1;

	sTempVector.clear();

	for (; left <= center && right <= end;)
	{
		if (*left <= *right)
		{
			sTempVector.emplace_back(*left);
			left++;
		}
		else
		{
			sTempVector.emplace_back(*right);
			right++;
		}
	}

	while (left <= center)
	{
		sTempVector.emplace_back(*left);
		left++;
	}

	while (right <= end)
	{
		sTempVector.emplace_back(*right);
		right++;
	}

	auto iterOriginal = begin;
	auto iterTemp = sTempVector.begin();

	for (; iterOriginal <= end;)
	{
		*iterOriginal = *iterTemp;
		iterTemp++;
		iterOriginal++;
	}
}