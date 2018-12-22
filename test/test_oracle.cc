#include <gtest/gtest.h>

#include <dionysus/simplex.h>

#include "ctag/point.h"
#include "ctag/oracle.h"

class OracleTest : public ::testing::Test {
public:
    typedef ctag::Point<double, 2> Point;
    typedef Point Direction;

    typedef dionysus::Simplex<Point> Simplex;
    typedef ctag::Oracle<Direction, Simplex> Oracle;
    typedef ctag::Diagram Diagram;
};

TEST_F(OracleTest, diagram) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});
    Point p5({5,2});
    Point p6({6,1});

    Simplex t({p1, p2, p3});
    Simplex e1({p2, p4});
    Simplex e2({p4, p6});
    Simplex e3({p6, p5});
    Simplex e4({p5, p4});

    Oracle oracle({ t, e1, e2, e3, e4 });

    Direction d({1,0});
    Diagram diagram = oracle.diagram(d);

    // Check 0th diagram
    Diagram::dim_const_iterator pair = diagram.begin(0);
    EXPECT_EQ(0, pair->birth);
    EXPECT_LT(100, pair->death);

    pair++;
    EXPECT_EQ(1, pair->birth);
    EXPECT_EQ(1, pair->death);

    pair++;
    EXPECT_EQ(2, pair->birth);
    EXPECT_EQ(2, pair->death);

    pair++;
    EXPECT_EQ(4, pair->birth);
    EXPECT_EQ(4, pair->death);

    pair++;
    EXPECT_EQ(5, pair->birth);
    EXPECT_EQ(5, pair->death);

    pair++;
    EXPECT_EQ(6, pair->birth);
    EXPECT_EQ(6, pair->death);

    pair++;
    EXPECT_EQ(diagram.end(0), pair);

    // Check 1st diagram
    pair = diagram.begin(1);
    EXPECT_EQ(2, pair->birth);
    EXPECT_EQ(2, pair->death);

    pair++;
    EXPECT_EQ(6, pair->birth);
    EXPECT_LT(100, pair->death);

    pair++;
    EXPECT_EQ(diagram.end(1), pair);
};

