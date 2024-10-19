#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Client.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Client.cpp"
#include <vector>
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Company.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Director.h"
TEST(TestClassName, TestClient) {
	setlocale(LC_ALL, "russian");
	Client new_client;
	new_client.setClientCash(10);
	new_client.setClientName("Bob");
	new_client.setClientEmail("Email");
	Order order;
	order.setName("order");
	order.setPrice(11);
	order.setInfoAboutOrder("info");
	EXPECT_EQ("order", order.getName());
	EXPECT_EQ(11, order.getPrice());
	EXPECT_EQ("info", order.getInfoAboutOrder());
	new_client.addBasket(order);
	new_client.doMainOrder();
	new_client.setClientCash(100000);
	new_client.doMainOrder();
	EXPECT_EQ("order", new_client.getBasketList()[0].getName());
	EXPECT_EQ(100000,new_client.getCash() );
	EXPECT_EQ("Bob", new_client.getName());
	EXPECT_EQ("Email", new_client.getEmail());
}
TEST(TestClassName, TestDirector) {
	Director director;
	Company lekar = director.showCompany();
	EXPECT_EQ(director.showCompany().getName(), lekar.getName());
	EXPECT_EQ(director.showCompany().showInfoAboutCompany(), lekar.showInfoAboutCompany());
	EXPECT_EQ(director.showCompany().getSuppliers()[0].getName(), lekar.getSuppliers()[0].getName());
}
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}