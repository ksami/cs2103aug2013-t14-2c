#include "TestParser.h"


TEST_F(TestParser, parse_emptystring_returnempty) {
	vector<string> result = parserUnderTest.parseString("");
	EXPECT_TRUE(result.empty());
}

TEST_F(TestParser, parse_simplestring_return2elements) {
	vector<string> result = parserUnderTest.parseString("Hello World!");
	EXPECT_EQ("Hello",result[0]);
	EXPECT_EQ("World!",result[1]);
}

TEST_F(TestParser, parse_undocmd_return1element) {
	vector<string> result = parserUnderTest.parseString("-undo");
	EXPECT_EQ("-undo",result[0]);
	EXPECT_EQ(1,result.size());
}

TEST_F(TestParser, parse_leadingspace_return1element) {
	vector<string> result = parserUnderTest.parseString(" 123asd");
	EXPECT_EQ("123asd",result[0]);
}

TEST_F(TestParser, parse_leadingspaces_return1element) {
	vector<string> result = parserUnderTest.parseString("   123asd");
	EXPECT_EQ("123asd",result[0]);
}

TEST_F(TestParser, parse_trailingspaces_return1element) {
	vector<string> result = parserUnderTest.parseString("123asd   ");
	EXPECT_EQ("123asd",result[0]);
	EXPECT_EQ(1,result.size());
}

TEST_F(TestParser, parse_multiplespaces_return1element) {
	vector<string> result = parserUnderTest.parseString("123   asd");
	EXPECT_EQ("123",result[0]);
	EXPECT_EQ("asd",result[1]);
}

TEST_F(TestParser, parse_specialchar1_returnempty) {
	vector<string> result = parserUnderTest.parseString("\n");
	EXPECT_TRUE(result.empty());
}

TEST_F(TestParser, parse_specialchar2_return2empty) {
	vector<string> result = parserUnderTest.parseString("\0");
	EXPECT_TRUE(result.empty());
}

