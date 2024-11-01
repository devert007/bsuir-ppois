
#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Mig.h"


TEST(test_class_mig, test_order_mig) {
	MIG mig;
	EXPECT_EQ(mig.getName(), "MIG");
	string expectedOutput = "ѕриобретите MIG. ¬ы больше не почувствуете боль в животе и нижних конечност€х\n";
	testing::internal::CaptureStdout();
	mig.help_without_pain();
	string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("BelFarm", mig.getSupplierName());
}