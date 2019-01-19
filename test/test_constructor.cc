#include <cmath>

#include <gtest/gtest.h>

#include "ctag/types.h"
#include "ctag/filtration_line.h"

#include "ctag/constructor.h"
#include "ctag/oracle.h"


class ConstructorTest : public ::testing::Test {
public:
    typedef ctag::Types::Point Point;
    typedef ctag::Types::Direction Direction;
    typedef ctag::FiltrationLine<Direction> FiltrationLine;
    typedef ctag::Constructor Constructor;
    typedef ctag::Diagram Diagram;

    typedef ctag::Oracle Oracle;
    typedef Oracle::Simplex Simplex;
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

TEST_F(ConstructorTest, min_angle) {
    Point p1({3,2});
    Point p2({2,1});
    Point p3({3,-1});
    Point p4({2,3});

    std::vector<Point> points = {p1, p2, p3, p4 };

    double min_angle = Constructor::min_angle(
            points.begin()+1,
            points.begin(), points.end());

    EXPECT_NEAR(M_PI/4., min_angle, .00001);
};

TEST_F(ConstructorTest, in_degree) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});

    Simplex et3({p2, p3});
    Simplex et2({p2, p1});
    Simplex e1({p2, p4});

    Oracle oracle({ et3, et2, e1 });

    Diagram diagram = oracle.diagram(Direction({0,1}));
    EXPECT_EQ(2, Constructor::in_degree(diagram, p2));

    diagram = oracle.diagram(Direction({1,0}));
    EXPECT_EQ(2, Constructor::in_degree(diagram, p2));

    diagram = oracle.diagram(Direction({-1,0}));
    EXPECT_EQ(1, Constructor::in_degree(diagram, p2));

    diagram = oracle.diagram(Direction({0,-1}));
    EXPECT_EQ(1, Constructor::in_degree(diagram, p2));
};

TEST_F(ConstructorTest, bowtie_directions) {
    Point p1({5,1});
    Point p2({5,2});

    std::pair<Direction, Direction> directions =
        Constructor::bowtie_directions(M_PI/10., p1, p2);

    EXPECT_NEAR(0.987688, directions.first[0], .000001);
    EXPECT_NEAR(0.156434, directions.first[1], .000001);

    EXPECT_NEAR(0.987688, directions.second[0], .000001);
    EXPECT_NEAR(-0.156434, directions.second[1], .000001);
}
