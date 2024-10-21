#pragma once
#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <string>
#include <vector>
#include "Company.h"

using namespace std;
class Order {
protected: 
	string name;
	double price;
	string info_about_order;
public:
	string getName() {
		return this->name;
	}
	double getPrice() {
		return this->price;
	}
	void setName(string new_name){
		this->name = new_name;
	}
	void setPrice(double new_price) {
		this->price = new_price;
	}
	string getInfoAboutOrder(){
		return this->info_about_order;
	}
	void setInfoAboutOrder(string info) {
		this->info_about_order=info;
	}
	virtual void complete_impact() {
		cout << "this is parent method\n";
	};
};

#endif