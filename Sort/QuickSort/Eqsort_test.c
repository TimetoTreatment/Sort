#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Eqsort(int ar[], int start, int end);
void Eqsort_recursive(int ar[], int start, int end);
void Tqsort(int ar[], int start, int end);

void Eqsort_test(int ar[], int start, int end)
{
	int Eqsort_time;
	int Tqsort_time;
	clock_t clock1;
	clock_t clock2;
	FILE* fp = fopen("numbers.txt", "r");

	clock1 = clock();
	Eqsort(ar, start, end);
	clock2 = clock();
	Eqsort_time = clock2 - clock1;

	for (int i = 0; i < end + 1; i++)
	{
		fscanf(fp, "%d", &ar[i]);
	}

	clock1 = clock();
	Tqsort(ar, start, end);
	clock2 = clock();
	Tqsort_time = clock2 - clock1;
	

	printf("%d\n%d\n", Eqsort_time, Tqsort_time);

	fclose(fp);
}