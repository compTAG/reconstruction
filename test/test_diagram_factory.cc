#include <gtest/gtest.h>

#include "ctag/diagram.h"
#include "ctag/diagram_factory.h"

class DiagramFactoryTest : public ::testing::Test {
public:
    typedef float Coordinate;
    typedef ctag::Point<Coordinate, 2> Point;
    typedef Point Direction;
    typedef dionysus::Simplex<Point> Simplex;
    typedef dionysus::Filtration<Simplex> Filtration;
    typedef ctag::HeightFunction<Simplex, Direction> HeightFunction;
    typedef ctag::FiltrationFactory<HeightFunction, Filtration> FiltrationFactory;

    typedef ctag::Diagram Diagram;
    typedef ctag::DiagramFactory<HeightFunction, Filtration> DiagramFactory;
};

TEST_F(DiagramFactoryTest, constructor) {
    Direction d({1,0});
    HeightFunction f(d);

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

    FiltrationFactory filt_factory;
    Filtration filtration = filt_factory.make_filtration(f, { t, e1, e2, e3, e4 });

    DiagramFactory diagram_factory;
    Diagram diagram = diagram_factory.make_diagram(f, filtration);

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

