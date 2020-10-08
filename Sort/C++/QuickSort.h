#pragma once
#include <random>

using namespace std;


class QuickSort
{
private:

	static random_device mSeed;
	static mt19937 mEngine;

	int FindPivot(int* ar, int start, int end)
	{
		uniform_int_distribution<int> distribution(start, end);
		return ar[distribution(mEngine)];
	}

	void Swap(int& left, int& right)
	{
		int temp = left;
		left = right;
		right = temp;
	}

	void InsertionSort(int* ar, int start, int end)
	{
		int i, j;
		int currentValue;

		for (i = start + 1; i <= end; i++)
		{
			currentValue = ar[i];

			for (j = i - 1; j >= start; j--)
			{
				if (ar[j] > ar[j + 1])
					Swap(ar[j], ar[j + 1]);
				else
					break;
			}

			ar[j] = currentValue;
		}
	}

	void rSort(int* ar, int start, int end)
	{
		if (end - start <= 10)
		{
			InsertionSort(ar, start, end);
			return;
		}

		int left;
		int right;
		int backupStart;
		int newEnd;
		int pivot = FindPivot(ar, start, end);

		for (left = start, right = end;;)
		{
			while (left <= right && ar[left] != pivot)
				left++;
			while (left <= right && ar[right] == pivot)
				right--;

			if (left < right)
				Swap(ar[left], ar[right]);
			else
				break;
		}

		backupStart = right + 1;

		for (left = start;;)
		{
			while (left <= right && ar[left] < pivot)
				left++;
			while (left <= right && ar[right] > pivot)
				right--;

			if (left < right)
				Swap(ar[left], ar[right]);
			else
				break;
		}

		newEnd = right;

		for (right = backupStart; right <= end; left++, right++)
			Swap(ar[left], ar[right]);

		rSort(ar, start, newEnd);
		rSort(ar, left, end);
	}


public:

	void Sort(int* ar, int size)
	{
		rSort(ar, 0, size - 1);
	}
};
