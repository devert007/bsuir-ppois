#pragma once
#ifndef HUMAN_H
#define HUMAN_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Human {
private:
	string name;
	int age;
public:
	int getAge() {
		return this->age;
	}
	string getName() {
		return this->name;
	}
protected:
	void setName(string new_name) {
		this->name = new_name;
	}
	void setAge(int new_age) {
		this->age = new_age;
	}
};

#endif