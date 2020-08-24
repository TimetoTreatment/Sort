#include "MergeSort.h"


void MergeSort::Sort(int* ar, int start, int end)
{
	if (start >= end)
		return;

	int center = (start + end) / 2;

	Sort(ar, start, center);
	Sort(ar, center + 1, end);

	int i;
	int left, right;
	int* newArray = new int[end - start + 1];
	int index;

	left = start;
	right = center + 1;

	for (index = 0; left <= center && right <= end;)
	{
		if (ar[left] <= ar[right])
		{
			newArray[index] = ar[left];
			left++;
			index++;
		}
		else
		{
			newArray[index] = ar[right];
			right++;
			index++;
		}
	}

	while (left <= center)
	{
		newArray[index] = ar[left];
		index++;
		left++;
	}

	while (right <= end)
	{
		newArray[index] = ar[right];
		index++;
		right++;
	}

	for (index = 0, i = start; i <= end; i++)
	{
		ar[i] = newArray[index];
		index++;
	}

	delete[] newArray;
}

