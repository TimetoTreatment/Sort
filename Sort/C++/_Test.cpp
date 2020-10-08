#include "_Test.h"

random_device _Test::mSeed;
mt19937 _Test::mEngine(_Test::mSeed());