#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/reconstructor.h"
#include "ctag/timer.h"

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
};
