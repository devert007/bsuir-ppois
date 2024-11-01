#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Headflex.h"

TEST(test_class_headflex, test_order_headflex) {
	HeadFlex headflex;
	EXPECT_EQ(headflex.getName(), "HeadFlex");
	EXPECT_EQ("OAO AptekaVDolg.by", headflex.getSupplierName());
	string expectedOutput = "Вам следует обратиться в нашему поставщику OAO AptekaVDolg.by за консультацией и приобрести HeadFlex\n";
	testing::internal::CaptureStdout();
	headflex.recomendations();
	string output = testing::internal::GetCapturedStdout();
}