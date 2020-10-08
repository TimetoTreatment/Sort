#pragma once
#include <random>

using namespace std;



class _Test
{
private:

	static random_device mSeed;
	static mt19937 mEngine;

	static int FindPivot(int* ar, int start, int end)
	{
		uniform_int_distribution<int> distribution(start, end);
		return ar[distribution(mEngine)];
	}

	static void Swap(int& left, int& right)
	{
		int temp = left;
		left = right;
		right = temp;
	}

	static void InsertionSort(int* ar, int start, int end)
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

	static void rSort(int* ar, int start, int end)
	{
		if (start >= end)
			return;

		int left, right;
		int i;
		int pivot = FindPivot(ar, start, end);

		left = i = start;
		right = end;

		for (; i <= right;)
		{
			if (ar[i] < pivot)
			{
				Swap(ar[left], ar[i]);
				left++;
				i++;
			}
			else if (ar[i] > pivot)
			{
				Swap(ar[right], ar[i]);
				right--;
			}
			else
				i++;
		}

		rSort(ar, start, left - 1);
		rSort(ar, right + 1, end);
	}


public:

	static void Sort(int* ar, int size)
	{
		rSort(ar, 0, size - 1);
	}
};

