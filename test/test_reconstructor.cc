#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/reconstructor.h"

class ReconstructorTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::SimplicialComplex SimplicialComplex;

    typedef ctag::Reconstructor<Oracle> Reconstructor;
};


TEST_F(ReconstructorTest, reconstruct_basic_example) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});

    Simplex t_e1({p1, p2});
    Simplex t_e2({p2, p3});
    Simplex t_e3({p3, p1});
    Simplex e1({p2, p4});

    Oracle oracle({ t_e1, t_e2, t_e3, e1 });

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
    EXPECT_EQ(0,0);
};

TEST_F(ReconstructorTest, reconstruct_simple_numerical_error) {
    Point p0({1,4});
    Point p1({12,45});
    Point p2({23,13});

    Simplex e1({p0, p2});
    Simplex e2({p1, p2});

    Oracle oracle({ e1, e2 });

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};

TEST_F(ReconstructorTest, reconstruct_verts_without_edges) {
    Point p0({1,4});
    Point p1({12,45});
    Point p2({23,13});

    Simplex s0({p0});
    Simplex s1({p1});
    Simplex s2({p2});

    Oracle oracle({ s0, s1, s2 });

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    EXPECT_TRUE(oracle.verify(result));
};
