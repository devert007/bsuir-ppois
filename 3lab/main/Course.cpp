#include "Course.h"
void Course:: setDiscountPrice() {
	for (int i = 0; i < this->sales.size(); i++) {
		this->price -= this->sales[i].getSaleValue();
	}
}
Course::Course() {}
Course::Course(string nameCourse, Teacher teacher,string info) {
	this->profession.setProfessionName(nameCourse);
	this->teacher = teacher;
	this->profession.setProfessionInfo(info);
}
int Course::getPrice() {
	return this->price;
}
void Course::setPrice(int price) {
	this->price = price;
	setDiscountPrice();
}
Teacher Course::getTeacher() {
	return this->teacher;
}
void Course::addSale(Sale new_sale) {
	this->sales.push_back(new_sale);
}
void Course::removeSale(int index) {
	this->sales.erase(this->sales.begin() + index);
}
vector<Sale> Course::getSales() {
	return this->sales;
}
Profession Course::getProfession() {
	return this->profession;
}
void Course::setInfoAboutCourse(const string& info) {
	this->profession.setProfessionInfo(info);
}