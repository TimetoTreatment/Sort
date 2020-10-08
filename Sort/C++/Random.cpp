#include "Random.h"

random_device Random::mSeed;
mt19937 Random::mEngine(Random::mSeed());