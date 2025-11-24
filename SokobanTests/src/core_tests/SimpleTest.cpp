#include <gtest/gtest.h>

// Ultra simple test with no dependencies
TEST(SimpleTest, BasicAssertion) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(SimpleTest, AnotherTest) {
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}
