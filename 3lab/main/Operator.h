#pragma once
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Employee.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Contact.h"
class Operator :public Employee {
private:
	Contact phone;
	Contact email;
public:
	Operator(string phoneNumber,string email);
	void changeOperatorNumber(string new_phoneNumber);
	void changeOperatorEmail(string new_emailNumber);

	string getOperatorPhone();
	string getOperatorEmail();
};
