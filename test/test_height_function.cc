#include <gtest/gtest.h>

#include <dionysus/simplex.h>
#include "ctag/point.h"

#include "ctag/height_filtration.h"

class HeightFunctionTest : public ::testing::Test {
public:
    typedef ctag::Point<double, 2> Point;
    typedef Point Direction;
    typedef dionysus::Simplex<Point> Simplex;
    typedef ctag::HeightFunction<Simplex, Direction> HeightFunction;

};

TEST_F(HeightFunctionTest, operator_eval_1d) {
    Direction d({1,0});
    HeightFunction f(d);

    Point p({5,2});
    Simplex v({p});
    EXPECT_EQ(5.0, f(v));
}

TEST_F(HeightFunctionTest, operator_eval_2d) {
    Direction d({0,-1});
    HeightFunction f(d);

    Point p1({5,2});
    Point p2({6,1});
    Simplex e({p1, p2});
    EXPECT_EQ(-1.0, f(e));
}

