#pragma once
#include <random>

using namespace std;


class Random
{
private:

	static random_device mSeed;
	static mt19937 mEngine;


public:

	static int Integer(int min, int max)
	{
		uniform_int_distribution<int> distribution(min, max);
		return distribution(mEngine);
	}
};
