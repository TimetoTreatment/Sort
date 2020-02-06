#include <stdio.h>


void FILE_read(int ar[], int num)
{
	FILE* fp = fopen("numbers.txt", "r");

	printf("\n ::Read numbers from numbers.txt\n ");

	for (int i = 0; i < num; i++)
	{
		fscanf(fp, "%d", &ar[i]);

		if (i % (num / 30) == 0)
			printf(".");
	}

	fclose(fp);
}