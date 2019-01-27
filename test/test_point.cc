#include <gtest/gtest.h>

#include "ctag/point.h"

class PointTest : public ::testing::Test {
public:
    typedef ctag::Point<double, 2> Point;
};

TEST_F(PointTest, lessThan) {
    EXPECT_TRUE(Point({0,0}) < Point({1,0}));
    EXPECT_TRUE(Point({0,0}) < Point({0,1}));
    EXPECT_FALSE(Point({0,0}) < Point({0,0}));
    EXPECT_FALSE(Point({1,0}) < Point({0,0}));
    EXPECT_FALSE(Point({0,1}) < Point({0,0}));
}
