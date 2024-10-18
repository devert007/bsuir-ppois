#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Manager.h"
#include <vector>
#include <string>
#include <iostream>
Order Manager::compare_an_order(int indexOfOrder) {
	Order order_to_return;
	if (indexOfOrder == 1) {
		MIG mig;
		return mig;
	}
	else if (indexOfOrder == 2) {
		HeadFlex headFlex;
		return headFlex;
	}
	else if (indexOfOrder == 3) {
		IBYPROFEN ibyprofen;
		return ibyprofen;
	}
	else if (indexOfOrder == 4) {
		ANTIGISTAT antigistat;
		return antigistat;
	}
	else if (indexOfOrder == 5) {
		ACETAMINOPHEN ACETAMINOPHEN;
		return ACETAMINOPHEN;
	}
	else if (indexOfOrder == 6) {
		ASPIRIN aspirin;
		return aspirin;
	}
	else if (indexOfOrder == 7) {
		DICLOFENAC diclofenac;
		return diclofenac;
	}
	else if (indexOfOrder == 8) {
		KETOROLAC ketorolac;
		return ketorolac;
	}
}
Order Manager::sayHelloAndMakeOrder() {
	std::cout << "Привет я твой персональный помощник " << this->getName() << " из компании Lekar.by.\n";
	int choose_idnex = 1;
	do {
		std::cout << "Выберите свой заказ:\n";
		std::cout << "1.MIG:\n";
		std::cout << "2.HeadFlex:\n";
		std::cout << "3.IBYPROFEN:\n";
		std::cout << "4.ANTIGISTAT:\n";
		std::cout << "5.ACETAMINOPHEN:\n";
		std::cout << "6.ASPIRIN:\n";
		std::cout << "7.DICLOFENAC:\n";
		std::cout << "8.KETOROLAC:\n";
		std::cout << "и пожалуйста введите номер заказа который вы хотите: \n";
		std::cin >> choose_idnex;
	} while (choose_idnex < 0 || choose_idnex > 9);
	return this->compare_an_order(choose_idnex);
}
Manager::Manager() {
	this->setName("Olesia");
	this->order_of_client = sayHelloAndMakeOrder();
}
Order Manager::sendAconfirmationToClient() {
	std::cout << "Ваш заказ: " << this->order_of_client.getName() << ".Цена: " << this->order_of_client.getPrice() << '\n';
	std::cout << "Все верно?(1-верно, 0-неверно): ";
	int choose_client = 0;
	std::cin >> choose_client;
	if (choose_client) {
		std::cout << "Спасибо за ваш заказ. Он поступил вам в корзину\n\n";
		return  this->order_of_client;
	}
	else {
		Order emptyOrder;
		emptyOrder.setName("");
		return emptyOrder;
	}
}