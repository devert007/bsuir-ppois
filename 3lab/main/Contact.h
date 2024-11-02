#pragma once
#include <iostream>
class Contact {
private:
	string nameOfContact;
	string info;
public:
	string getNameContact() {
		return this->nameOfContact;
	}
	string getContact() {
		return this->info;
	}
	void setContact(string info) {
		this->info = info;
	}
	void setContactName(string name) {
		this->nameOfContact = name;
	}
};