void Eqsort_recursive_old(int ar[], int start, int end)
{
	if (end - start < 1)
		return;

	int i, j;
	int norm, norm_index, temp;
	int a = ar[start + (end - start) / 4];
	int b = ar[start + (end - start) / 2];
	int c = ar[start + 3 * (end - start) / 4];

	// V1 START
	/*

	norm_index = start;
	norm = ar[start];

	*/
	// V1 END


	// V2 START

	if ((a > b&& a < c) || (a < b && a > c))
	{
		norm = a;
		norm_index = start + (end - start) / 4;
	}
	else if ((c > a&& c < b) || (c < a && c > b))
	{
		norm = c;
		norm_index = start + 3 * (end - start) / 4;
	}
	else
	{
		norm = b;
		norm_index = start + (end - start) / 2;
	}

	// V2 END


	for (i = start, j = end;;)
	{
		while ((ar[i] < norm && i < j))
		{
			if (i == end)
				break;
			i++;
		}

		while ((ar[j] > norm&& j > i))
		{
			if (j == start)
				break;
			j--;
		}

		if (j == i)
			break;

		if (ar[i] == ar[j])
			j--;
		else
		{
			temp = ar[i];
			ar[i] = ar[j];
			ar[j] = temp;
		}
	}

	Eqsort_recursive_old(ar, start, j - 1);
	Eqsort_recursive_old(ar, j + 1, end);
}