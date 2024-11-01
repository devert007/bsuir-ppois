
#include <gtest/gtest.h>

#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Company.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Director.h"

TEST(test_class_director, test_company) {
	Director director;
	Company lekar = director.showCompany();
	EXPECT_EQ(director.showCompany().getName(), lekar.getName());
	EXPECT_EQ(director.showCompany().showInfoAboutCompany(), lekar.showInfoAboutCompany());
	EXPECT_EQ(director.showCompany().getSuppliers()[0].getName(), lekar.getSuppliers()[0].getName());
}