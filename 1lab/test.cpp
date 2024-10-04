#include "pch.h"
#include "D:/LABY/BSUIR/1labaPPOIS/Longint.h"
#include "D:/LABY/BSUIR/1labaPPOIS/Longint.cpp"
TEST(TestCaseConstructor1, defaultConstructor) {
	Longint a;
	a.setLong("123");
	EXPECT_EQ(a.getLong(), "123");
	EXPECT_TRUE(true);
}
TEST(TestCaseConstructor2, InitConstructor) {
	Longint a("-111");
	EXPECT_EQ(a.getLong(), "-111");
	EXPECT_TRUE(true);
}
TEST(TestCaseConstructor3, LongNumberConstructor) {
	Longint a("-22435678294652832222200000");

	EXPECT_EQ(a.getLong(), "-22435678294652832222200000");
	EXPECT_TRUE(true);
}
TEST(TestCaseSize, LongNumberSize) {
	Longint a("-22435678294652832222200000");

	EXPECT_EQ(a.size(), 26);
	EXPECT_TRUE(true);
}


TEST(TestCaseSum1, TestA_plus_B_Sum) {
	Longint a("22435670");
	Longint b("-22435670");
	EXPECT_EQ("0", (a + b).getLong());
	EXPECT_EQ("0", (b + a).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseSum2, TestA_plus_B_Sum) {
	Longint a("12345");
	Longint d("-123");
	Longint e("-123");
	EXPECT_EQ("-246", (d + e).getLong());
	Longint c = a + 1;
	ASSERT_EQ(c.getLong(), a++.getLong());
	a--;
	Longint b("12345");
	EXPECT_EQ("24690", (a + b).getLong());
	EXPECT_EQ("24690", (a + 12345).getLong());
	EXPECT_EQ("24690", (a += 12345).getLong());
	a -= 12345;
	EXPECT_EQ("24690", (a += b).getLong());
	EXPECT_TRUE(true);
}



TEST(TestCaseSub1, TestA_plus_B_Sub) {
	Longint a("22435670");
	Longint b("-22435670");
	EXPECT_EQ("44871340", (a - b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseSub2, TestA_plus_B_Sub) {
	Longint a("12345");
	Longint b("12345");
	EXPECT_EQ("0", (a - b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseSub3, TestA_plus_B_Sub) {
	Longint a("-12345");
	Longint b("12345");
	Longint c("-12345");
	Longint d("-12344");
	EXPECT_EQ("-1", (a - d).getLong());
	EXPECT_EQ("-24690", (a - b).getLong());
	EXPECT_EQ("-24690", (a - 12345).getLong());
	EXPECT_EQ("0", (a - c).getLong());
	EXPECT_EQ("-12346", (a--).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseSub4, TestA_plus_B_Sub) {
	Longint a("12345");
	EXPECT_EQ("0", (a - 12345).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseSub5, TestA_plus_B_Sub) {
	Longint a("12345");
	Longint b("12345");
	EXPECT_EQ("0", (a -= b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseSub6, TestA_plus_B_Sub) {
	Longint a("12345");
	EXPECT_EQ("0", (a -= 12345).getLong());
	EXPECT_TRUE(true);
}


TEST(TestCaseMult1, TestA_mult_B_is) {
	Longint a("987654321");
	Longint b("987654321");
	EXPECT_EQ("975461057789971041", (a * b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseMult2, TestA_mult_B_is) {
	Longint a("987654321");
	Longint b("-987654321");
	EXPECT_EQ("-975461057789971041", (a * b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseMult3, TestA_mult_B_is) {
	Longint a("-987654321");
	Longint b("-987654321");
	EXPECT_EQ("975461057789971041", (a * b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseMult4, TestA_mult_B_is) {
	Longint a("-987654321");
	EXPECT_EQ("-12192592592745", (a * 12345).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseMult5, TestA_mult_B_is) {
	Longint a("-987654321");
	Longint b("-987654321");
	b *= 12345;
	EXPECT_EQ(b.getLong(), (a *= 12345).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseMult6, TestA_mult_B_is) {
	Longint a("-987654321");
	Longint b("-12345");
	EXPECT_EQ("12192592592745", (a *= b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseDiv1, TestA_div_B_is) {
	Longint a("12345");
	EXPECT_EQ("0", (a / 0).getLong());
	Longint b("-12345");
	EXPECT_EQ("-1", (a / b).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseDiv2, TestA_div_B_is) {
	Longint a("12000");
	Longint b("-1000");
	EXPECT_EQ("-12", (a / b).getLong());
	EXPECT_EQ("-12", (a /= b).getLong());
	EXPECT_EQ("-1", (a /= 12).getLong());
	EXPECT_EQ("1", (a / -1).getLong());
	EXPECT_TRUE(true);
}
TEST(TestCaseCompare) {
	Longint a("-15129");
	Longint b("-123");
	Longint c("-123");
	Longint d("123");
	EXPECT_TRUE(a < b);
	EXPECT_TRUE(a <= b);
	EXPECT_TRUE(b > a);
	EXPECT_TRUE(b >= a);
	EXPECT_TRUE(a < 1);
	EXPECT_TRUE(b > (-124));
	EXPECT_TRUE(a <= 0);
	EXPECT_FALSE(b < c);
	EXPECT_TRUE(b >= (-123));
	EXPECT_FALSE(b >= (-122));
	EXPECT_FALSE(b >= (-122));
	EXPECT_TRUE(b <= c);
	EXPECT_TRUE(b >= c);
	EXPECT_TRUE(d >= -123);
	EXPECT_FALSE(b >= 123);
	EXPECT_FALSE(d < (-123));
	EXPECT_TRUE(d >= (-123));
	EXPECT_TRUE(d > (-123));
	EXPECT_FALSE(d <= (-123));
	EXPECT_FALSE(d <= (122));
	EXPECT_TRUE(d <= (124));
	EXPECT_FALSE(d <= b);
	EXPECT_FALSE(d < b);
	EXPECT_TRUE(b < d);
	EXPECT_FALSE(b > d);
}









int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}