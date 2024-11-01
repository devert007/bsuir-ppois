#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace std;
#include <vector>

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}