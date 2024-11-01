#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Ketorelac.h"

TEST(test_class_ketorolac, test_order_ketorolac) {
	Ketorolac ketorolac;
	EXPECT_EQ(ketorolac.getName(), "KETOROLAC");
	EXPECT_EQ("RussianFarm", ketorolac.getSupplierName());
	string expectedOutput = "Препарат KETOROLAC если он вам необходим, проконсультируйтесь с вашим специалистом.\n";
	testing::internal::CaptureStdout();
	ketorolac.getDoctorRecipe();
	string output = testing::internal::GetCapturedStdout();
}