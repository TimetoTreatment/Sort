#include <stdlib.h>


void Eqsort_old(int ar[], int start, int end)
{
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//	
	// * Ascending Sort Function * //	
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

	/*								*
		1. ar[] = array to sort
		2. start = first of array
		3. end = last of array
	*								*/

	int temp, i, j;
	int norm, norm_25, norm_50, norm_75;
	int End_of_array = end;
	int* check = (int*)calloc(end + 1, sizeof(int));

	for (i = 0; i <= End_of_array;)
	{
		if (end - start <= 1)
		{
			if (ar[start] > ar[end])
			{
				temp = ar[start];
				ar[start] = ar[end];
				ar[end] = temp;
			}
			start = end + 1;
		}
		else
		{
			norm_25 = ar[start + (end - start) / 4];
			norm_50 = ar[start + (end - start) / 2];
			norm_75 = ar[start + 3 * (end - start) / 4];

			if ((norm_25 > norm_50&& norm_25 < norm_75) || (norm_25 < norm_50 && norm_25 > norm_75))
				norm = norm_25;
			else if ((norm_75 > norm_25&& norm_75 < norm_50) || (norm_75 < norm_25 && norm_75 > norm_50))
				norm = norm_75;
			else
				norm = norm_50;

			for (i = start, j = end; i <= j;)
			{
				while (ar[i] < norm)
					i++;

				while (ar[j] > norm)
					j--;

				if (i <= j)
				{
					if (ar[i] != ar[j])
					{
						temp = ar[i];
						ar[i] = ar[j];
						ar[j] = temp;
					}

					i++;
					j--;
				}
			}

			if (start < j)
			{
				check[start] = 1;
				check[j] = 2;
			}
			else
			{
				check[start + 1] = 1;
				start++;
			}
			if (i < end)
			{
				check[i] = 1;
				check[end] = 2;
			}
			else
			{
				check[end - 1] = 2;
				check[end] = 0;
			}
		}

		for (i = start; i < End_of_array; i++)
		{
			if (check[i] == 1)
			{
				start = i;
				break;
			}
		}
		for (i = start + 1; i <= End_of_array; i++)
		{
			if (check[i] == 2)
			{
				end = i;
				break;
			}
		}
	}

	free(check);
}