#include "_EmperorSort.h"

random_device EmperorSort::mSeed;
mt19937 EmperorSort::mEngine(EmperorSort::mSeed());


int EmperorSort::FindPivot(int* ar, int start, int end)
{
	uniform_int_distribution<int> distribution(start, end);
	return ar[distribution(mEngine)];
}


void EmperorSort::Swap(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}


void EmperorSort::InsertionSort(int* ar, int start, int end)
{
	int i, j;
	int currentValue;

	for (i = end - 1; i >= start; i--)
	{
		currentValue = ar[i];

		for (j = i + 1; j <= end && ar[j] < currentValue; j++)
			ar[j - 1] = ar[j];

		ar[j - 1] = currentValue;
	}
}


void EmperorSort::rSort(int* ar, int start, int end)
{
	if (end - start <= 5)
	{
		InsertionSort(ar, start, end);
		return;
	}

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