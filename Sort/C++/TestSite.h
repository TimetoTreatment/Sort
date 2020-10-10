#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "Timer.h"
#include "__TestSort.h"
#include "_EmperorSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"

using namespace std;


class TestSite
{
private:

	EmperorSort mEmperor;
	TestSort mTest;
	QuickSort mQuick;
	MergeSort mMerge;
	HeapSort_Array mHeapArray;
	HeapSort_List mHeapList;

	Timer mTimer;
	int* mArray;
	int* mArrayDup;
	int mArraySize;
	char mRandomArray;
	int mMenu;

	void Prompt();
	void Sort();
	void initialize();
	bool ErrorCheck();

	TestSite()
	{
		mArray = nullptr;
		mArrayDup = nullptr;
		mArraySize = 0;
		mRandomArray = false;
		mMenu = 0;
	}

	~TestSite()
	{
		delete mArray;
		delete mArrayDup;
	}

public:

	void Main();


private:

	static TestSite* sInstance;

public:
	static TestSite* Instance()
	{
		if (sInstance == nullptr)
			sInstance = new TestSite;

		return sInstance;
	}

	static void Release()
	{
		delete sInstance;
		sInstance = nullptr;
	}
};

