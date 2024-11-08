#include <D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Client.h>
#include <vector>
#include <string>
#include <iostream>
Client::Client() {
}
Client :: Client(RegMenu menu) {

	menu.makeRegistration();
	this->email = menu.getEmail();
	setName(menu.getName());
	this->cash = menu.getCash();
}

string Client::getEmail() {
	return this->email;
}
int Client::getCash() {
	return this->cash;
}
void Client::addBasket(Order orderOfClient) {
	basket.push_back(orderOfClient);
}
vector<Order> Client::getBasketList() {
	
	return this->basket;
}
void Client::deleteFromBasket(int choose_client=1) {

	this->basket.erase(basket.begin() + choose_client - 1);

}
void Client::doMainOrder() {

	int sumOfAllBusket = 0;
	for (int i = 0; i < basket.size(); i++) {
		sumOfAllBusket += basket[i].getPrice();
	}
	if (sumOfAllBusket > cash) {
		cout << "� ��� ������������ �������. ��������� ���� ��� ������� ��� ���� �� �������.\n";
		return;
	}
	else if (basket.size() != 0) {
		cout << "������� �� ��� �����. �� ����� ��������� � ��� � ���������� �����.\n";
	}
	else {
		cout << "���� ������� �����\n";
	}
}
void Client::setClientName(string new_name) {
	setName(new_name);
}
void Client::setClientEmail(string new_email) {
	this->email=(new_email);
}
void Client::setClientCash(int new_cash) {
	this->cash = (new_cash);
}
