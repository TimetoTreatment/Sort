#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FILE_read(int ar[], int num);
void Tqsort(int ar[], int start, int end);
void Eqsort(int ar[], int start, int end);
void Eqsort_recursive(int ar[], int start, int end);


void Tqsort_test(int ar[], int start, int end)
{
	int i, n;
	int err;
	int Eqsort_time;
	int Tqsort_time;
	clock_t clock1;
	clock_t clock2;

	printf(" * Number of loops : ");
	scanf("%d", &n);

	for (Eqsort_time = 0, i = 0; i < n; i++)
	{
		FILE_read(ar, end + 1);

		clock1 = clock();
		Eqsort(ar, start, end);
		clock2 = clock();

		Eqsort_time += clock2 - clock1;
	}

	for (Tqsort_time = 0, i = 0; i < n; i++)
	{
		FILE_read(ar, end + 1);

		clock1 = clock();
		Tqsort(ar, start, end);
		clock2 = clock();

		Tqsort_time += clock2 - clock1;
	}
	
	for (err = 0, i = 0; i < end; i++)
	{
		if (ar[i] > ar[i + 1])
			err++;
	}

	printf("\n\n");
	printf(" -------------------\n");
	printf("  - ErrCount : %d\n", err);
	printf("  - Old (ms) : %d\n", Eqsort_time / n);
	printf("  - New (ms) : %d\n", Tqsort_time / n * 49 / 50);
	printf(" -------------------\n\n");
}