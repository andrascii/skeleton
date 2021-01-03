#include "Api.h"

namespace dataapitests {

TEST(ApiTests, GetSomeNumber1Test) {
  EXPECT_EQ(dataapi::GetSomeNumber1(), 42);
}

TEST(ApiTests, GetSomeNumber2Test) {
  EXPECT_DOUBLE_EQ(dataapi::GetSomeNumber2(), 3.1415);
}

TEST(ApiTests, HelloWorldTest) {
  EXPECT_EQ(dataapi::HelloWorld(), "Hello World"s);
}

}
