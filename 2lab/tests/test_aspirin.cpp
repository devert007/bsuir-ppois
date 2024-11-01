#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Aspirin.h"

TEST(test_class_aspirin, test_order_aspirin) {
	Aspirin aspirin;
	EXPECT_EQ(aspirin.getName(), "ASPIRIN");
	EXPECT_EQ("TyanShiFarm", aspirin.getSupplierName());
	string expectedOutput = "Вам станет легче после вчерашней вечеринки, чувствуйте себя огурчиком после препарата ASPIRIN\n";
	testing::internal::CaptureStdout();
	aspirin.helpAfterParty();
	string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(aspirin.getTheLastDayOfFarm(), 19102025);
}