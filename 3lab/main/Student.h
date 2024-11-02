#pragma once
#include <iostream>
#include "Human.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Course.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Certificate.h"
class Student : public Human {
private:
	Course current_course;
	int stageOfCourse;
	vector<Course> all_courses;
public:
	Student() {};
	Student(Course course){
		this->current_course =course;
		this->all_courses.push_back(course);
		this->stageOfCourse = 0;
	};
	void doHomework() {
		if (this->current_course.getTeacher().setHomework(2)) {
			
			this->stageOfCourse++;
		}
	}
	int getStudentStage() {
		return this->stageOfCourse;
	}
	Course getStudentCourse() {
		return this->current_course;
	}
	Certificate getCertificate() {
		if (this->stageOfCourse >= 5) {
			Certificate certificate_stud(this->getNameandSurname(), this->getStudentCourse(), this->stageOfCourse);
			return certificate_stud;
		}
		else return Certificate() ;
	}
	void addCourse(Course new_course) {
		this->all_courses.push_back(new_course);
	}

	void changeCurrentCourse(int index) {
		this->current_course = this->all_courses.at(index);
	}
	vector<Course> getAllCourses() {
		return this->all_courses;
	}
};