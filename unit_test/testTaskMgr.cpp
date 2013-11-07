//@Kenneth A0097075W

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
	testString.push_back("-details");
	testString.push_back("simple");
	testString.push_back("valid");
	testString.push_back("case");
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
	testString.push_back("-details");
	testString.push_back("overlap");
	testString.push_back("time");
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
	testString.push_back("-details");
	testString.push_back("overlap");
	testString.push_back("date");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_missingParameter_returntrue) {
	vector<string> testString;
	testString.push_back("-startdate");
	testString.push_back("");
	testString.push_back("-enddate");
	testString.push_back("");
	testString.push_back("-starttime");
	testString.push_back("");
	testString.push_back("-endtime");
	testString.push_back("");
	testString.push_back("-details");
	testString.push_back("");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_TRUE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_duplicatedParameter_returnFalse) {
	vector<string> testString;
	testString.push_back("-startdate");
	testString.push_back("-startdate");
	testString.push_back("-details");
	testString.push_back("-details");
	testString.push_back("");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_invliadStartDate_returnFalse) {
	vector<string> testString;
	testString.push_back("-startdate");	
	testString.push_back("hudjs");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_invliadStartTime_returnFalse) {
	vector<string> testString;
	testString.push_back("-starttime");	
	testString.push_back("hudjs");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_invliadEndDate_returnFalse) {
	vector<string> testString;
	testString.push_back("-enddate");	
	testString.push_back("hudjs");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_invliadEndTime_returnFalse) {
	vector<string> testString;
	testString.push_back("-endtime");	
	testString.push_back("hudjs");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
}

TEST_F(testTaskMgr, create_emptystorage_noParameter_returnTrue) {
	vector<string> testString;
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_TRUE(createTaskSuccess);
}
