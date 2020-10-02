#pragma once
class QuickSort
{
public:

	static void Sort(int ar[], int start, int end)
	{
		//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//	
		// * Ascending Sort Function * //	
		//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
		/*                              *
			1. ar[] = array to sort
			2. start = first of array
			3. end = last of array
		*                               */

		int i, j, temp;
		int pivot;
		int pivotList[3];

		for (i = 0; i < 3; i++)
			pivotList[i] = ar[(end - start) * (i + 1) / 4 + start];

		for (i = 0; i < 2; i++)
		{
			for (j = i + 1; j <= 2; j++)
			{
				if (pivotList[i] > pivotList[j])
				{
					temp = pivotList[i];
					pivotList[i] = pivotList[j];
					pivotList[j] = temp;
				}
			}
		}

		pivot = pivotList[1];

		for (i = start, j = end;; i++, j--)
		{
			while (ar[i] < pivot) i++;
			while (ar[j] > pivot) j--;

			if (i > j)
				break;

			if (i < j)
			{
				temp = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
			}
		}

		if (start < j)	Sort(ar, start, j);
		if (i < end)	Sort(ar, i, end);
	}
};