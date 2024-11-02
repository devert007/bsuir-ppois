#pragma once
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Employee.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Contact.h"

class Manager :public Employee {
private:
	Contact phone;
	Contact email;
public:
	Manager(string phoneNumber, string email);
	void changeManagerNumber(string new_phoneNumber);
	void changeManagerEmail(string new_emailNumber);

	string getManagerPhone();
	string getManagerEmail();
};