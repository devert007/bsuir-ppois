#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Manager.h"

Manager::Manager(string phoneNumber, string email) {
	this->phone.setContactName(phoneNumber);
	this->email.setContactName(email);
}
void Manager::changeManagerNumber(string new_phoneNumber) {
	this->phone.setContactName(new_phoneNumber);
}
void Manager::changeManagerEmail(string new_emailNumber) {
	this->email.setContactName(new_emailNumber);
}

string Manager::getManagerPhone() {
	return this->phone.getContact();
}
string Manager::getManagerEmail() {
	return this->email.getContact();
}