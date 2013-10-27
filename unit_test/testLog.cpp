#include "testLog.h"
 
// Tests if time can be retrieved
TEST_F(testLog, getCurrentTime_returnfalse) {
	std::string result = Log::getCurrentTime();
	EXPECT_FALSE(result.empty());
}