#include "gtest/gtest.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Student.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Course.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Certificate.h"




TEST(test_class_student, test_online_student) {
	string professionInfo2 = "professionInfo2";
	Course course1("PPOIS help course", Teacher("Davyd", "Davydov"), professionInfo2);
	course1.setPrice(95);
	Student student(course1);
	student.setNameAndSurname("ivan", "kislitsyn");
	//student.setSex("male");
	

	EXPECT_EQ(student.getNameandSurname(), "ivan kislitsyn");
	//EXPECT_EQ(student.getSex(), "male");
	EXPECT_EQ(student.getStudentStage(), 0);
	student.doHomework();
	EXPECT_EQ(student.getStudentStage(), 1);
	student.doHomework();

	student.doHomework();

	student.doHomework();

	student.doHomework();

	student.doHomework();

	Certificate certificate = student.getCertificate();
	EXPECT_EQ(certificate.getSertificateInfoAsVector()[1], "PPOIS help course");
	EXPECT_EQ(certificate.getSertificateInfoAsVector()[0], "ivan kislitsyn");


}