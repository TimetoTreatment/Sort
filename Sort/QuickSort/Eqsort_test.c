#include <stdlib.h>

void Eqsort_test(int ar[], int start, int end)
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

		if (j - start == 1)
		{
			if (ar[start] > ar[j])
			{
				temp = ar[start];
				ar[start] = ar[j];
				ar[j] = temp;
			}
		}
		else if (start < j)
		{
			stack[index - 1] = start;
			stack[index] = j;

			index += 2;
		}

		if (end - i == 1)
		{
			if (ar[i] > ar[end])
			{
				temp = ar[end];
				ar[end] = ar[i];
				ar[i] = temp;
			}
		}
		else if (i < end)
		{
			stack[index - 1] = i;
			stack[index] = end;

			index += 2;
		}
	}

	free(stack);
}
