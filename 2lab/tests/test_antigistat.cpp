#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Antigistat.h"

TEST(test_class_antigistat, test_order_antigistat) {
	Antigistat antigistat;
	EXPECT_EQ(antigistat.getName(), "ANTIGISTAT");
	EXPECT_EQ("TyanShiFarm", antigistat.getSupplierName());
	string expectedOutput = "Принимайте препарат ANTIGISTAT больше двух недель и инфекция ослабнет\n";
	testing::internal::CaptureStdout();
	antigistat.destroy_infection();
	string output = testing::internal::GetCapturedStdout();

}