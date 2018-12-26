#include <gtest/gtest.h>

#include "ctag/types.h"

class PointTest : public ::testing::Test {
public:
    typedef ctag::Types::Point Point;
};

TEST_F(PointTest, dist) {
    Point p1({0,1});
    Point p2({2,0});

    EXPECT_NEAR(std::sqrt(5), p1.dist(p2), .00001);
};


