#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 2000000

int ar[NUM];

void Tqsort_test(int ar[], int start, int end);
void Eqsort(int ar[], int start, int end);
void Eqsort_recursive(int ar[], int start, int end);
void Eqsort_old(int ar[], int start, int end);
void Eqsort_recursive_old(int ar[], int start, int end);
void FILE_read(int ar[], int num);

void function_menu(void)
{
	printf("\n");
	printf(" 0 <- Tqsort_test\n");
	printf(" 1 <- Eqsort\n");
	printf(" 2 <- Eqsort_recursive\n");
	printf(" 3 <- Eqsort_old\n");
	printf(" 4 <- Eqsort_recursive_old\n");
	printf("\n");
}

int main(void)
{
	int i;
	int err;
	int function;
	clock_t clock1;
	clock_t clock2;


	function_menu();

	do {
		printf(" * Select Function Number to Test : ");
		scanf("%d", &function);

	} while (function < 0 || function > 4);

	if (function == 0)
	{
		Tqsort_test(ar, 0, NUM - 1);
	}
	else
	{
		FILE_read(ar, NUM);
		printf("\n\n ::Sorting %d numbers...\n\n", NUM);

		clock1 = clock();
		switch (function)
		{
			case 1: Eqsort(ar, 0, NUM - 1); break;
			case 2: Eqsort_old(ar, 0, NUM - 1); break;
			case 3: Eqsort_recursive(ar, 0, NUM - 1); break;
			case 4: Eqsort_recursive_old(ar, 0, NUM - 1);  break;
		}
		clock2 = clock();

		for (err = 0, i = 1; i < NUM; i++)
		{
			if (ar[i - 1] > ar[i])
				err++;
		}

		printf(" -------------------\n");
		printf("  - ErrCount : %d\n", err);
		printf("  - Time(ms) : %d\n", clock2 - clock1);
		printf(" -------------------\n\n");
	}


	return 0;
}