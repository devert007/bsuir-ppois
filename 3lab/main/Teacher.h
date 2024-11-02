#pragma once
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Employee.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Human.h"
class Teacher :public Employee {
private:
	string profile;
	string education;
	int stageHomework=0;
public:
	Teacher(string name,string surname) {
		setNameAndSurname(name, surname);
		this->setSalaryForEmployee(1800);
	}
	Teacher(){}
	void setProfile(string profile) {
		this->profile = profile;
	}
	void setEducation(string education) {
		this->education = education;
	}
	string getProf() {
		return this->profile;
	}
	string getEdu() {
		return this->education;
	}
	bool setHomework(int stage) {
		
		this->stageHomework=stage;
		return true;
	}
	int getStageHomework() {
		return this->stageHomework;
	}
};