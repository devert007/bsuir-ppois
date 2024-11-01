#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include <string>
#include "Order.h"
#include "Human.h"
#include "RegistrationMenu.h"
using namespace std;
class Client:public Human {
private:
	string email;
	vector<Order>basket;
	int cash;
public:
	Client(RegMenu);
	Client();
	string getEmail();
	int getCash();
	void addBasket(Order orderOfClient);
	vector<Order> getBasketList();
	void deleteFromBasket(int choose_client);
	void setClientName(string new_name);
	void setClientEmail(string new_email);
	void setClientCash(int new_cash);
	void doMainOrder();
	
};



#endif