#include "gtest/gtest.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Teacher.h"



TEST(test_class_teacher, test_online_teacher) {
	Teacher teacher("ivan", "testsurname");
	teacher.setEducation("higher");
	teacher.setProfile("AI");
	teacher.setSalaryForEmployee(1500);
	EXPECT_EQ(teacher.getNameandSurname(), "ivan testsurname");
	EXPECT_EQ(teacher.getEdu(), "higher");
	EXPECT_EQ(teacher.getProf(), "AI");
	EXPECT_EQ(teacher.getSalaryOfEmployee(), 1500);




}