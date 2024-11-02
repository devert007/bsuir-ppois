#pragma once
#include <string>
#include <vector>
#include "Sale.h"
#include "Teacher.h"
#include "Sale.h"
#include "Profession.h"
using namespace std;
class Course {
private:
	Profession profession;
	Teacher teacher;
	vector<Sale> sales;
	int price;
	void setDiscountPrice();

public:
	Course();
	Course(string nameCourse, Teacher teacher,string info);
	int getPrice();
	void setPrice(int price);
	Teacher getTeacher();
	void addSale(Sale new_sale);
	void removeSale(int index);
	void setInfoAboutCourse(const string&info);
	vector<Sale>getSales();
	Profession getProfession();
};