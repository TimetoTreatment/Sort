#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;



class _Test
{
	typedef struct Vector2i
	{
		int value[2];

	} Vector2i;

	static void Swap(int* left, int* right)
	{
		int temp = *left;
		*left = *right;
		*right = temp;
	}

	static int FindPivot(int* ar, int start, int end)
	{
		return ar[rand() % (end - start + 1) + start];
	}

	static Vector2i Partition(int* ar, int start, int end)
	{
		int left;
		int right;
		int backupStart;
		int newEnd;
		int pivot = FindPivot(ar, start, end);

		for (left = start, right = end;;)
		{
			while (right >= start && ar[right] == pivot)
				right--;

			while (left < right && ar[left] != pivot)
				left++;

			if (left < right)
				Swap(&ar[left], &ar[right]);
			else
				break;
		}

		backupStart = right + 1;

		for (left = start; left <= right;)
		{
			while (left <= right && ar[left] < pivot)
				left++;
			while (left <= right && ar[right] > pivot)
				right--;

			if (left < right)
				Swap(&ar[left], &ar[right]);
		}

		newEnd = right;

		for (right = backupStart; right <= end; left++, right++)
			Swap(&ar[left], &ar[right]);

		return Vector2i { newEnd, left };
	}

	static void QuickSort(int* ar, int start, int end)
	{
		if (start < end)
		{
			Vector2i index = Partition(ar, start, end);
			QuickSort(ar, start, index.value[0]);
			QuickSort(ar, index.value[1], end);
		}
	}

public:

	static void Sort(int* ar, int size)
	{
		srand(time(NULL));
		QuickSort(ar, 0, size - 1);
	}
};

