//@author A0097075W

#include "testTaskMgr.h"

TEST_F(testTaskMgr, create_emptystorage_emptystring_returntrue) {
	vector<string> testString;
	testString.push_back("-add");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_TRUE(createTaskSuccess);
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

TEST_F(testTaskMgr, create_emptystorage_missingParameter_returnfalse) {
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
	testString.push_back("-add");
	bool createTaskSuccess = taskMgrUnderTest.createTask(testString, stubTaskStorage);
	EXPECT_FALSE(createTaskSuccess);
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


//@author A0101885E
TEST_F(testTaskMgr, testSearchKeyBlank) {
	Task test1, test2, test3;
	test1.assignDetails("testing 1");
	test1.assignDetails("testing 2");
	test1.assignDetails("testing 3");
	vector<Task> testStorage;
	testStorage.push_back(test1);
	testStorage.push_back(test2);
	testStorage.push_back(test3);
	vector<Task> search;
	bool createTaskSuccess=taskMgrUnderTest.searchKeyBlank(testStorage,search,"test");
	EXPECT_TRUE(createTaskSuccess);
}

TEST_F(testTaskMgr, testFindIdPos) {
	Task test1, test2, test3;
	test1.assignIDNumber(10);
	test2.assignIDNumber(20);
	test3.assignIDNumber(30);
	vector<Task> testStorage;
	testStorage.push_back(test1);
	testStorage.push_back(test2);
	testStorage.push_back(test3);
	int test=taskMgrUnderTest.findIDPos(20,testStorage);
	EXPECT_EQ(1,test);
}

TEST_F (testTaskMgr, testCheckID_true) {
	int random;
	Task test1, test2, test3;
	test1.assignIDNumber(10);
	test2.assignIDNumber(20);
	test3.assignIDNumber(30);
	vector<Task> testStorage;
	testStorage.push_back(test1);
	testStorage.push_back(test2);
	testStorage.push_back(test3);
	bool createTaskSuccess=taskMgrUnderTest.checkID(20,testStorage,random);
	EXPECT_TRUE(createTaskSuccess);
}

TEST_F (testTaskMgr, testCheckID_false) {
	int random;
	Task test1, test2, test3;
	test1.assignIDNumber(10);
	test2.assignIDNumber(20);
	test3.assignIDNumber(30);
	vector<Task> testStorage;
	testStorage.push_back(test1);
	testStorage.push_back(test2);
	testStorage.push_back(test3);
	bool createTaskSuccess=taskMgrUnderTest.checkID(40,testStorage,random);
	EXPECT_FALSE(createTaskSuccess);
}



