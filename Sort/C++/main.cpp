#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include "Console.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;


int main(void)
{
	Console* console = Console::Instance();

	chrono::steady_clock::time_point startClock;
	chrono::duration<double> elapsedClock;

	int* ar;
	int* inputArray;
	int size;
	bool RandomArray = false;
	int menu = 0;

	cout << "Enter size of array : ";
	cin >> size;
	inputArray = new int[size];
	ar = new int[size];

	cout << "Fill an array with random numbers? : ";
	cin >> RandomArray;

	if (!RandomArray)
	{
		cout << "Fill array elements : ";
		for (int i = 0; i < size; i++)
			cin >> inputArray[i];
	}
	else
	{
		ifstream file("numbers.txt", ios_base::in);

		for (int i = 0; i < size; i++)
			file >> inputArray[i];

		file.close();
	}

	cout << endl;
	cout << "********************" << endl;
	cout << "* Choose Algorithm *" << endl;
	cout << "********************" << endl;

	cout << " 1. C++ Sort" << endl;
	cout << " 2. MergeSort" << endl;
	cout << " 3. QuickSort" << endl;
	cout << " 0. Exit" << "\n\n";

	for (;;)
	{
		cin >> menu;

		if (menu == 0)
			break;

		for (int i = 0; i < size; i++)
			ar[i] = inputArray[i];

		startClock = chrono::steady_clock::now();

		switch (menu)
		{
		case 1:
			sort(ar, ar + size);
			break;

		case 2:
			MergeSort::Sort(ar, 0, size - 1);
			break;

		case 3:
			QuickSort::Sort(ar, 0, size - 1);
			break;
		}

		elapsedClock = chrono::steady_clock::now() - startClock;

		bool errorDetected = false;

		for (int i = 1; i < size; i++)
		{
			if (ar[i - 1] > ar[i])
			{
				errorDetected = true;
				break;
			}
		}

		if (errorDetected)
			cout << "Error Detected!" << "\n\n";
		else
		{
			cout.precision(6);
			cout << fixed << elapsedClock.count() << "\n\n";
		}
	}

	delete[] ar;
	delete[] inputArray;

	return 0;
}