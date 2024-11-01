#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Ibyprofen.h"

TEST(test_class_ibuprofen, test_order_ibuprofen) {
	Ibuprofen ibuprofen;
	EXPECT_EQ(ibuprofen.getName(), "IBUPROFEN");
	EXPECT_EQ("IndiaTea", ibuprofen.getSupplierName());
	string expectedOutput = "Вам станет гораздо лучше после применения препарата IBUPROFEN в течение 1 часа после его приема.\n";
	testing::internal::CaptureStdout();
	ibuprofen.complete_impact();
	string output = testing::internal::GetCapturedStdout();
}