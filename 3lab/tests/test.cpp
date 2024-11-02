
#include "gtest/gtest.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Human.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Human.cpp"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Operator.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Operator.cpp"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Student.h"

#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Certificate.h"

#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Course.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Course.cpp"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Manager.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Manager.cpp"

#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Profession.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Sale.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Teacher.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/OnlinePlatform.h"



/*TEST(MainTest, testAllfunctions) {
	OnlinePlatform platform("ITppois.bsuir", "we help with ppois in BSUIR");
	vector<string> contacts = { "3752912345","ppoisCourse@bsuir.by","375441234597","courseMan@bsuir.by" };
	platform.setContacts(contacts);
	Comment comment1(3, "its the best online platform");
	Comment comment2(4, "Empowering students");
	Comment comment3(5, "Connecting BSUIR students");
	vector<Comment>comments = { comment1,comment2,comment3 };
	platform.setComments(comments);
	string info1 = "Профессия AI (Искусственный интеллект, AI)";

	//
	//create courses and sales for them
	Course course1("AI profession", Teacher("Ivan", "Ivanov"), info1);
	Sale sale1(12);
	course1.addSale(sale1);
	course1.setPrice(120);

	





	Student student(course1);
	student.getStudentCourse().getTeacher().setHomework(10);
	student.setNameAndSurname("ivan", "kislitsyn");
	student.setSex('male');
	student.getNameandSurname();
	student.getStudentCourse().getProfession().getProfessionName();
	student.getStudentCourse().getPrice();
	student.getStudentCourse().getSales()[0].getSaleValue();
	student.doHomework();
	student.doHomework();
	student.doHomework();
	student.doHomework();
	student.doHomework();
	student.doHomework();
	Certificate certificate = student.getCertificate();
	student.getStudentStage();
	
}

*/