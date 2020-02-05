#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 1000000

int ar[NUM];

void Eqsort(int ar[], int start, int end);
void Eqsort_recursive(int ar[], int start, int end);
void Eqsort_old(int ar[], int start, int end);
void Eqsort_recursive_old(int ar[], int start, int end);
void Eqsort_test(int ar[], int start, int end);


int main(void)
{
	int i;
	int function;
	int err;
	FILE* fp = fopen("numbers.txt", "r");


	printf("\n 1 : Eqsort\n 2 : Eqsort_recursive\n 3 : Eqsort_old\n 4 : Eqsort_recursive_old\n 5 : Eqsort_TEST\n\n");

	do
	{
		printf(" Select Function Number to Test : ");
		scanf("%d", &function);
	} while (function < 1 || function > 5);

	printf("\n Read numbers from numbers.txt\n ");

	for (i = 0; i < NUM; i++)
	{
		fscanf(fp, "%d", &ar[i]);

		if (i % (NUM / 28) == 0)
			printf(".");
	}

	fclose(fp);

	printf("\n\n Sorting %d numbers...\n\n", NUM);

	clock_t start = clock();

	switch (function)
	{
		case 1: Eqsort(ar, 0, NUM - 1); break;
		case 2: Eqsort_old(ar, 0, NUM - 1); break;
		case 3: Eqsort_recursive(ar, 0, NUM - 1); break;
		case 4: Eqsort_recursive_old(ar, 0, NUM - 1); break;
		case 5: Eqsort_test(ar, 0, NUM - 1);
	}

	clock_t end = clock();

	for (err = 0, i = 1; i < NUM; i++)
	{
		if (ar[i - 1] > ar[i])
			err++;
	}

	printf(" -------------------\n");
	printf("  - ErrCount : %d\n", err);
	printf("  - Time(ms) : %d\n", end - start);
	printf(" -------------------\n\n");


	return 0;
}