#pragma once
#include <string>
#include <vector>
#include "Student.h"
using namespace std;
class Certificate {
private:
	Course course;
	string name_and_surname;
	string mark;
public:
	Certificate(){}
	Certificate(string name_surname,Course course,int stage){
		this->course =course;
		this->name_and_surname = name_surname;
		this->mark = (to_string((stage + 10) / 5));
	}
	vector<string> getSertificateInfoAsVector() {
		vector<string> info_return{this->name_and_surname,
								   this->course.getProfession().getProfessionName(),
								   this->mark};
		return info_return;
	}
};