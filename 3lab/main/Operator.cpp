#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Operator.h"

Operator::Operator(string phoneNumber,string email) {
	this->phone.setContactName(phoneNumber);
	this->email.setContactName(email);
}
void Operator::changeOperatorNumber(string new_phoneNumber) {
	this->phone.setContactName(new_phoneNumber);
}
void Operator::changeOperatorEmail(string new_emailNumber) {
	this->email.setContactName(new_emailNumber);
}

string Operator::getOperatorPhone() {
	return this->phone.getContact();
}
string Operator::getOperatorEmail() {
	return this->email.getContact();
}