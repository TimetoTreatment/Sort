#include "TestSite.h"

int main(void)
{
	TestSite::Instance()->Main();
	TestSite::Release();

	return 0;
}