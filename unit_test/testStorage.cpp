#include "testStorage.h"

TEST_F(testStorage, createStorage) {
	EXPECT_EQ("unnamed", storageUnderTest.getStorageName());
}

TEST_F(testStorage, SafeToOpenOutPutStreamBeforeOpen) {
	EXPECT_TRUE(storageUnderTest.isSafeToOpenStream());
}

TEST_F(testStorage, FailToOpenOutPutStreamAfterOpen){
	storageUnderTest.initialOutputStream();
	EXPECT_FALSE(storageUnderTest.isSafeToOpenStream());
}

TEST_F(testStorage, SafeToOpenOutPutStreamAfterOpenThenClose){
	storageUnderTest.initialOutputStream();
	EXPECT_FALSE(storageUnderTest.isSafeToOpenStream());
	storageUnderTest.closeOutputStream();
	EXPECT_TRUE(storageUnderTest.isSafeToOpenStream());
}

TEST_F(testStorage, SafeToOpenInPutStreamBeforeOpen) {
	EXPECT_TRUE(storageUnderTest.isSafeToOpenStream());
}

TEST_F(testStorage, FailToOpenInPutStreamAfterOpen){
	storageUnderTest.initialInputStream();
	EXPECT_FALSE(storageUnderTest.isSafeToOpenStream());
}

TEST_F(testStorage, SafeToOpenInPutStreamAfterOpenThenClose){
	storageUnderTest.initialInputStream();
	EXPECT_FALSE(storageUnderTest.isSafeToOpenStream());
	storageUnderTest.closeInputStream();
	EXPECT_TRUE(storageUnderTest.isSafeToOpenStream());
}

TEST_F(testStorage, retrieveRealDetails){
	EXPECT_EQ("BLANKED", storageUnderTest.retrieveRealDetails(""));
	EXPECT_EQ("TESTING", storageUnderTest.retrieveRealDetails("TESTING"));
}