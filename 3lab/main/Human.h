#pragma once
#include <string>
using namespace std;
class Human {
private:
	string name;
	string surname;
	bool sex; // 1 - male, 0 - female
public:
	string getNameandSurname();
	void setNameAndSurname(string new_name, string new_surname);
	bool getSex();
	void setSex(bool new_sex);
};