#pragma once
#ifndef COMPANY_H
#define COMPANY_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Company {
protected:
	string name;
	string info;
	vector<Company> suppliers;
public:
	string showInfoAboutCompany() {
		return  this->info;
	}
	string setName(string name) {
		this->name = name;
		return this->name;
	}
	string setInfo(string info) {
		this->info = info;
		return this->info;
	}
	string getName() {
		return this->name;
	}
	void setSuppliers(vector<string>suppliersNames) {
		
		for (int i = 0; i < suppliersNames.size(); i++) {
			this->suppliers.push_back(Company());
			this->suppliers[i].setName(suppliersNames[i]);
			this->suppliers[i].setInfo( suppliers[i].getName()+".com");
		}
	}
	vector<Company> getSuppliers() {
		return this->suppliers;
	}
};



#endif