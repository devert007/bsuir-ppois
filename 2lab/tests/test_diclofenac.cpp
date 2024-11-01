#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Diclofenac.h"

TEST(test_class_diclofenac, test_order_diclofenac) {
	Diclofenac diclofenac;
	EXPECT_EQ(diclofenac.getName(), "DICLOFENAC");
	EXPECT_EQ("BelAptekaFarm", diclofenac.getSupplierName());
	string expectedOutput = "ѕримите DICLOFENAC. ∆дите когда подействует препарат, в течении получаса боль снизитс€\n";
	testing::internal::CaptureStdout();
	diclofenac.destroy_headache();
	string output = testing::internal::GetCapturedStdout();
}