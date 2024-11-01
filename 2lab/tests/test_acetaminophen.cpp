#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Acetaminophen.h"

TEST(test_class_acetaminophen, test_order_acetaminophen) {
	Acetaminophen acetaminophen;
	EXPECT_EQ(acetaminophen.getName(), "ACETAMINOPHEN");
	EXPECT_EQ("TyanShiFarm", acetaminophen.getSupplierName());
    string expectedOutput = "Перед употреблением ACETAMINOPHEN советуем убедиться, что у вас не аллергии на данный препарат.\n";
	testing::internal::CaptureStdout();
	acetaminophen.getAcetaminopehForClient();
	string output = testing::internal::GetCapturedStdout();

}