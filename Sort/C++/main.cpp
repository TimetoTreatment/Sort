#include <iostream>
#include <chrono>
#include <algorithm>
#include "Console.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;

enum class Type
{
	Array,
	Vector,
};


int main(void)
{
	Console* console = Console::Instance();

	chrono::steady_clock::time_point startClock;
	chrono::duration<double> elapsedClock;

	int* arrayOut;
	int* arrayIn;
	int arraySize;
	bool RandomArray = false;
	int menu = 0;

	Type type = Type::Vector;
	vector<int> vec;
	vector<int> vecOut;

	cout << "Enter size of array : ";
	cin >> arraySize;
	arrayIn = new int[arraySize];
	arrayOut = new int[arraySize];
	vec.reserve(arraySize);

	cout << "Fill an array with random numbers? : ";
	cin >> RandomArray;

	if (!RandomArray)
	{
		cout << "Fill array elements : ";
		for (int i = 0; i < arraySize; i++)
		{
			cin >> arrayIn[i];
			vec.emplace_back(arrayIn[i]);
		}
	}
	else
	{
		ifstream file("numbers.txt", ios_base::in);

		for (int i = 0; i < arraySize; i++)
		{
			file >> arrayIn[i];
			vec.emplace_back(arrayIn[i]);
		}

		file.close();
	}

	cout << endl;
	cout << "********************" << endl;
	cout << "* Choose Algorithm *" << endl;
	cout << "********************" << endl;

	cout << " 1. C++ Sort" << endl;
	cout << " 2. QuickSort" << endl;
	cout << " 3. MergeSort (Array)" << endl;
	cout << " 4. MergeSort (Vector)" << endl;
	cout << " 0. Exit" << "\n\n";

	for (;;)
	{
		cin >> menu;

		if (menu == 0)
			break;
		else if (menu == 4)
			type = Type::Vector;
		else
			type = Type::Array;

		switch (type)
		{
		case Type::Array:
			for (int i = 0; i < arraySize; i++)
				arrayOut[i] = arrayIn[i];
			break;

		case Type::Vector:
			vecOut = vec;
			break;
		}

		startClock = chrono::steady_clock::now();

		switch (menu)
		{
		case 1:
			sort(arrayOut, arrayOut + arraySize);
			break;

		case 2:
			QuickSort::Sort(arrayOut, 0, arraySize - 1);
			break;

		case 3:
			MergeSort::Sort(arrayOut, arrayOut + arraySize);
			break;

		case 4:
			MergeSort::Sort(vecOut.begin(), vecOut.end());
			break;
		}

		elapsedClock = chrono::steady_clock::now() - startClock;

		bool errorDetected = false;

		if (menu == 1 || menu == 2 || menu == 3)
		{
			for (int i = 1; i < arraySize; i++)
			{
				if (arrayOut[i - 1] > arrayOut[i])
				{
					errorDetected = true;
					break;
				}
			}
		}
		else if (menu == 4)
		{
			for (auto iter = vecOut.begin() + 1; iter != vecOut.end(); iter++)
			{
				if (*(iter - 1) > * iter)
				{
					errorDetected = true;
					break;
				}
			}
		}

		if (errorDetected)
		{
			cout << "Error Detected!" << "\n\n";
		}
		else
		{
			cout.precision(6);
			cout << fixed << elapsedClock.count() << "\n\n";
		}
	}

	delete[] arrayOut;
	delete[] arrayIn;

	return 0;
}