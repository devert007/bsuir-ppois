#include "gtest/gtest.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Course.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Sale.h"





TEST(test_class_course, test_online_course) {
	string professionInfo2 = "professionInfo2";
	Course course1("PPOIS help course", Teacher("Davyd", "Davydov"), professionInfo2);
	course1.setPrice(95);
	Sale sale(10);
	course1.addSale(sale);
	EXPECT_EQ(course1.getSales()[0].getSaleValue(), 10);
	EXPECT_EQ(course1.getPrice(), 95);
	EXPECT_EQ(course1.getTeacher().getNameandSurname(), "Davyd Davydov");
	course1.removeSale(0);
	EXPECT_EQ(0, course1.getSales().size());
}