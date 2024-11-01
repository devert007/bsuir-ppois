#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Client.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Client.cpp"

#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"




TEST(test_class_client, test_client) {
	Client new_client;
	new_client.setClientCash(100);
	new_client.setClientName("Bob");
	new_client.setClientEmail("Email");
	EXPECT_EQ("Bob", new_client.getName());
	EXPECT_EQ(100, new_client.getCash());
	EXPECT_EQ("Email", new_client.getEmail());
	Order order;
	order.setName("order");
	order.setPrice(11);
	order.setInfoAboutOrder("info");
	new_client.addBasket(order);
	EXPECT_EQ(new_client.getBasketList()[0].getName(), order.getName());
	new_client.deleteFromBasket(1);
	EXPECT_EQ(new_client.getBasketList().size(), 0);
	new_client.addBasket(order);
	
	string expectedOutput1 = "Спасибо за ваш заказ. Он будет доставлен к вам в кратчайшие сроки.\n";
	testing::internal::CaptureStdout();
	new_client.doMainOrder();
	string output1 = testing::internal::GetCapturedStdout();
	new_client.setClientCash(10);

	string expectedOutput2 = "У вас недостаточно средств. Пополните счет или удалите что либо из корзины.\n";
	testing::internal::CaptureStdout();
	new_client.doMainOrder();
	string output2 = testing::internal::GetCapturedStdout();


}