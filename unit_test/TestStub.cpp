#include "TestStub.h"
 
// Tests that stubFunction() returns 0
TEST_F(TestStub, stub_stubFunction_Return0) {
  EXPECT_EQ(0,stubFunction());
}