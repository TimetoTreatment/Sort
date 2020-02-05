#include <stdlib.h>

void Tqsort(int ar[], int start, int end)
{
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//	
	// * Ascending Sort Function * //	
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
	/*								*
		1. ar[] = array to sort
		2. start = first of array
		3. end = last of array
	*								*/

	if (end - start < 1)
		return;

	int i, j, temp;
	int pivot;
	int pivot_list[3];
	int* stack;
	int index;

	stack = (int*)malloc((end - start) * sizeof(int));
	if (stack == NULL) exit(-1);

	stack[0] = start;
	stack[1] = end;

	for (index = 1; index > 0; index -= 2)
	{
		start = stack[index - 1];
		end = stack[index];

		for (i = 0; i < 3; i++)
		{
			pivot_list[i] = ar[(end - start) * (i + 1) / 4 + start];
		}

		for (i = 0; i < 2; i++)
		{
			for (j = i + 1; j <= 2; j++)
			{
				if (pivot_list[i] > pivot_list[j])
				{
					temp = pivot_list[i];
					pivot_list[i] = pivot_list[j];
					pivot_list[j] = temp;
				}
			}
		}

		pivot = pivot_list[1];

		for (i = start, j = end;; i++, j--)
		{
			while (ar[i] < pivot)
				i++;

			while (ar[j] > pivot)
				j--;

			if (i > j)
				break;

			if (i < j)
			{
				temp = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
			}
		}

		if (start < j)
		{
			stack[index - 1] = start;
			stack[index] = j;

			index += 2;
		}

		if (i < end)
		{
			stack[index - 1] = i;
			stack[index] = end;

			index += 2;
		}
	}

	free(stack);
}