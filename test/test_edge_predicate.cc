#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/edge_predicate.h"

class EdgePredicateTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::Complex Complex;

    typedef ctag::EdgePredicate<Oracle> EdgePredicate;
};

TEST_F(EdgePredicateTest, op) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});

    Complex simplices = {
        Simplex({p1, p2}),
        Simplex({p3})
    };

    Oracle oracle(simplices.begin(), simplices.end());

    double bowtie_angle = M_PI/20;
    EdgePredicate predicate(bowtie_angle);


    EXPECT_TRUE(predicate(oracle, p1, p2));
    EXPECT_FALSE(predicate(oracle, p1, p3));
    EXPECT_FALSE(predicate(oracle, p2, p3));
};
