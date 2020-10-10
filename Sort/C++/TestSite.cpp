#include "TestSite.h"

TestSite* TestSite::sInstance = nullptr;


void TestSite::Prompt()
{
	cout << "Enter size of array : ";
	cin >> mArraySize;

	cout << "Fill an array with random numbers? (Y/N) : ";
	cin >> mRandomArray;

	if (mRandomArray == 'N' || mRandomArray == 'n')
		mRandomArray = false;
	else
		mRandomArray = true;

	cout << endl;
	cout << "********************" << endl;
	cout << "* Choose Algorithm *" << endl;
	cout << "********************" << endl;

	cout << " 1. My Sort" << endl;
	cout << " 2. C++ Sort" << endl;
	cout << " 3. QuickSort" << endl;
	cout << " 4. MergeSort" << endl;
	cout << " 5. HeapSort (Array)" << endl;
	cout << " 6. HeapSort (List)" << endl;
	cout << " 0. Exit" << "\n\n";
}


void TestSite::Sort()
{
	switch (mMenu)
	{
	case -1:
		mTest.Sort(mArrayDup, mArraySize);
		break;

	case 1:
		mEmperor.Sort(mArrayDup, mArraySize);
		break;

	case 2:
		std::sort(mArrayDup, mArrayDup + mArraySize);
		break;

	case 3:
		mQuick.Sort(mArrayDup, mArraySize);
		break;

	case 4:
		mMerge.Sort(mArrayDup, mArrayDup + mArraySize);
		break;

	case 5:
		mHeapArray.Sort(mArrayDup, mArraySize);
		break;

	case 6:
		mHeapList.Sort(mArrayDup, mArraySize);
		break;
	}
}


void TestSite::initialize()
{
	mArray = new int[mArraySize];
	mArrayDup = new int[mArraySize];

	if (!mRandomArray)
	{
		cout << "Fill array elements : ";

		for (int i = 0; i < mArraySize; i++)
			cin >> mArray[i];
	}
	else
	{
		ifstream file("numbers.txt", ios_base::in);

		for (int i = 0; i < mArraySize; i++)
			file >> mArray[i];

		file.close();
	}
}


bool TestSite::ErrorCheck()
{
	for (int i = 1; i < mArraySize; i++)
	{
		if (mArrayDup[i - 1] > mArrayDup[i])
			return true;
	}

	return false;
}


void TestSite::Main()
{
	Prompt();
	initialize();

	for (;;)
	{
		int repeatCount = 10;
		double totalElapsedTime = 0;

		cin >> mMenu;

		if (mMenu == 0)
			break;

		for (int count = 0; count < repeatCount; count++)
		{
			for (int i = 0; i < mArraySize; i++)
				mArrayDup[i] = mArray[i];

			mTimer.Reset();
			Sort();
			totalElapsedTime += mTimer.ElapsedTime();
		}

		if (ErrorCheck())
			cout << "Error Detected!";
		else
		{
			cout.precision(10);
			cout << fixed << totalElapsedTime / repeatCount;
		}

		cout << "\n\n";
	}
}