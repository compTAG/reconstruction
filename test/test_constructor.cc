#include <gtest/gtest.h>

#include "ctag/types.h"
#include "ctag/filtration_line.h"

#include "ctag/constructor.h"


class ConstructorTest : public ::testing::Test {
public:
    typedef ctag::Types::Point Point;
    typedef ctag::Types::Direction Direction;
    typedef ctag::FiltrationLine<Direction> FiltrationLine;
    typedef ctag::Constructor Constructor;
};

TEST_F(ConstructorTest, intersect) {
    FiltrationLine l1(Direction({1,0}), 4);
    FiltrationLine l2(Direction({0.16662,0.002777}), 0.669259);
    Point p = Constructor::intersect(l1, l2);

    EXPECT_NEAR(4, p[0], .001);
    EXPECT_NEAR(1, p[1], .001);
};

TEST_F(ConstructorTest, dist) {
    Point p1({0,1});
    Point p2({2,0});

    double dist = Constructor::distance(p1, p2);
    EXPECT_NEAR(std::sqrt(5), dist, .00001);
};

