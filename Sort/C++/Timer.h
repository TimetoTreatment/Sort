#pragma once
#include <chrono>

using namespace std::chrono;

class Timer
{
private:

	steady_clock::time_point mStart;


public:

	void Reset()
	{
		mStart = steady_clock::now();
	}

	double ElapsedTime()
	{
		return duration<double> (steady_clock::now() - mStart).count();
	}
};

