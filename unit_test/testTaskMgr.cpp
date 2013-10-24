#include "testTaskMgr.h"


TEST_F(testTaskMgr, create_emptystorage_emptystring_returnfalse) {
	vector<string> testString;
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_simplevalidstring_returntrue) {
	vector<string> testString;
	testString.push_back("-startdate");
	testString.push_back("121212");
	testString.push_back("-enddate");
	testString.push_back("121212");
	testString.push_back("-starttime");
	testString.push_back("1212");
	testString.push_back("-endtime");
	testString.push_back("1213");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_TRUE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_overlaptime_returnfalse) {
	vector<string> testString;
	testString.push_back("-startdate");
	testString.push_back("121212");
	testString.push_back("-enddate");
	testString.push_back("121212");
	testString.push_back("-starttime");
	testString.push_back("1212");
	testString.push_back("-endtime");
	testString.push_back("1210");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_overlapdate_returnfalse) {
	vector<string> testString;
	testString.push_back("-startdate");
	testString.push_back("121212");
	testString.push_back("-enddate");
	testString.push_back("121210");
	testString.push_back("-starttime");
	testString.push_back("1212");
	testString.push_back("-endtime");
	testString.push_back("1212");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}