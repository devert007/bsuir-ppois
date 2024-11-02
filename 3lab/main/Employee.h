#pragma once
#include "Human.h"
class Employee: public Human{
protected:
	int salary;
public:
	int getSalaryOfEmployee() {
		return this->salary;
	}
	void setSalaryForEmployee(int new_salary) {
		this->salary = new_salary;
	}
};