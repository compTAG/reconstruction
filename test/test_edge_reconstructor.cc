#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/edge_reconstructor.h"

class EdgeReconstructorTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Simplex Simplex;

    typedef ctag::EdgeReconstructor<Oracle> EdgeReconstructor;
};

TEST_F(EdgeReconstructorTest, reconstruct_basic_example) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});

    Simplex t_e1({p1, p2});
    Simplex t_e2({p2, p3});
    Simplex t_e3({p3, p1});
    Simplex e1({p2, p4});

    Oracle oracle({ t_e1, t_e2, t_e3, e1 });

    std::vector<Point> points = { p1, p2, p3, p4 };

    typedef typename std::vector<Point>::const_iterator PIter;
    std::vector< std::pair< PIter, PIter> > edges;

    EdgeReconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(edges),
            oracle, points.begin(), points.end());

    auto ei = edges.begin();
    EXPECT_EQ(p1, *(ei->first));
    EXPECT_EQ(p2, *(ei->second));

    ++ei;
    EXPECT_EQ(p1, *(ei->first));
    EXPECT_EQ(p3, *(ei->second));

    ++ei;
    EXPECT_EQ(p2, *(ei->first));
    EXPECT_EQ(p3, *(ei->second));

    ++ei;
    EXPECT_EQ(p2, *(ei->first));
    EXPECT_EQ(p4, *(ei->second));
}

TEST_F(EdgeReconstructorTest, angle_error) {
    Point p1({0,0});
    Point p2({1,0});
    Point p3({1,0.0000005});

    Simplex e1({p1, p2});
    Simplex e2({p2, p3});

    Oracle oracle({ e1, e2 });

    std::vector<Point> points = { p1, p2, p3 };

    typedef typename std::vector<Point>::const_iterator PIter;
    std::vector< std::pair< PIter, PIter> > edges;

    EdgeReconstructor reconstructor;

    ASSERT_THROW({
        reconstructor.reconstruct(std::back_inserter(edges),
                oracle, points.begin(), points.end());
    }, std::range_error);
};
