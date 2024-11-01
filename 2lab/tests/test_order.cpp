#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace std;
#include <vector>

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"



TEST(test_class_order, test_order) {
	setlocale(LC_ALL, "russian");
	Order order;
	order.setName("order");
	order.setPrice(11);
	order.setInfoAboutOrder("info");
	EXPECT_EQ("order", order.getName());
	EXPECT_EQ(11, order.getPrice());
	EXPECT_EQ("info", order.getInfoAboutOrder());
}

