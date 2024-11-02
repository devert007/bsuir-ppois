
#include "gtest/gtest.h"
#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/Comment.h"

#include "D:/LABY/BSUIR/PPOIS/3laba_PPOIS/OnlinePlatform.h"
TEST(test_class_online_platform, test_online_platform) {
	OnlinePlatform platform("ITppois.bsuir", "we help with ppois in BSUIR");
	EXPECT_EQ(platform.getName(), "ITppois.bsuir");
	EXPECT_EQ(platform.getOrientation(), "we help with ppois in BSUIR");
	vector<string> contacts = { "3752912345","ppoisCourse@bsuir.by","375441234597","courseMan@bsuir.by" };
	platform.setContacts(contacts);
	Comment comment1(3, "its the best online platform");
	Comment comment2(4, "Empowering students");
	Comment comment3(5, "Connecting BSUIR students");
	vector<Comment>comments = { comment1,comment2,comment3 };
	platform.setComments(comments);
	EXPECT_EQ(platform.getCommentsArray()[0].getCommentStars(), comments[0].getCommentStars());
	EXPECT_EQ(platform.getCommentsArray()[1].getCommentInfo(), comments[1].getCommentInfo());
	EXPECT_EQ(platform.getContact()[0].getContact(), contacts[0]);

}