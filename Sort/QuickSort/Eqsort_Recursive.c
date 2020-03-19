void Eqsort_recursive(int ar[], int start, int end)
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
	int pivot_list[3];


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

	for (i = start, j = end; i <= j; i++, j--)
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

	if (start < j)
		Eqsort_recursive(ar, start, j);

	if (i < end)
		Eqsort_recursive(ar, i, end);
}