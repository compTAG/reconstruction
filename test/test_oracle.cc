#include <gtest/gtest.h>

#include "ctag/oracle.h"

class OracleTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Direction Direction;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::SimplicialComplex SimplicialComplex;
    typedef Oracle::Diagram Diagram;
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

TEST_F(OracleTest, verify) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p3b({1,3.00005});
    Point p3c({1,3.5});
    Point p4({4,1});

    Simplex et3({p2, p3});
    Simplex et3b({p2, p3b});
    Simplex et3c({p2, p3c});
    Simplex et2({p2, p1});
    Simplex e1({p2, p4});

    Simplex en({p3, p4});

    SimplicialComplex s1 = { et3, et2, e1 };
    Oracle oracle(s1.begin(), s1.end());

    SimplicialComplex s2 = { e1, et3, et2 };
    SimplicialComplex s2b = { e1, et3b, et2 };
    SimplicialComplex s2c = { e1, et3c, et2 };
    SimplicialComplex s3 = { e1, et3, en };

    EXPECT_TRUE(oracle.verify(s2));
    EXPECT_TRUE(oracle.verify(s2b));
    EXPECT_FALSE(oracle.verify(s2c));
    EXPECT_FALSE(oracle.verify(s3));
}

TEST_F(OracleTest, verify_no_edges) {
    Point p1({0,0});
    Point p2({2,2});

    Simplex s1({p1});
    Simplex s2({p2});
    Simplex e2({p1, p2});

    SimplicialComplex c1 = { s1, s2 };
    Oracle oracle(c1.begin(), c1.end());

    SimplicialComplex c2 = { e2 };
    SimplicialComplex c3 = { s2, s1 };

    EXPECT_TRUE(oracle.verify(c1));
    EXPECT_TRUE(oracle.verify(c3));
    EXPECT_FALSE(oracle.verify(c2));
}

