#include "Human.h"
string Human::getNameandSurname() {
	return this->name + " " + this->surname;
}
void Human::setNameAndSurname(string new_name, string new_surname) {
	this->name = new_name;
	this->surname = new_surname;
}
bool Human ::getSex() {
	return this->sex;
}
void Human::setSex(bool new_sex) {
	this->sex = new_sex;
}