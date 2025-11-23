#include "pch.h"
#include "Position.h"

TEST(PositionTest, Equality) {
    Position p1(1, 2);
    Position p2(1, 2);
    EXPECT_TRUE(p1 == p2);
}

TEST(PositionTest, Inequality) {
    Position p1(1, 2);
    Position p2(9, 9);
    EXPECT_TRUE(p1 != p2);
}