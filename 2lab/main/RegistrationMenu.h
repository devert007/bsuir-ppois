#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;



class RegMenu {
private:
	string nameOfClient;
	string emailOfClient;
	int cash;
	void getNameFromUser() {
		cout << "_________________________________________________" << '\n';
		cout << "|Пожалуйста введите ваше имя:" << '\t';
		string input_name;
		cin >> input_name;
		this->nameOfClient = input_name;
	}
	void getEmailFromUser() {
		cout << "______________________________________________________" << '\n';
		cout << "|Пожалуйста введите вашу почту:" << '\t';
		string input_email;
		cin >> input_email;
		this->emailOfClient = input_email;
	}
	void getCashFromUser() {
		cout << "___________________________________________________" << '\n';
		cout << "|Пожалуйста введите вашу сумму(баланс):" << '\t';
		int input_cash;
		cin >> input_cash;
		this->cash = input_cash;
	}
public:
	
	void makeRegistration() {
		getNameFromUser();
		getEmailFromUser();
		getCashFromUser();
	}
	string getName() {
		return this->nameOfClient;
	}
	string getEmail() {
		return this->emailOfClient;
	}
	int getCash() {
		return this->cash;
	}
};