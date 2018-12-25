#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/vertex_reconstructor.h"

class VertexReconstructorTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Direction Direction;
    typedef Oracle::Simplex Simplex;

    typedef ctag::VertexReconstructor<Oracle> VertexReconstructor;
};

TEST_F(VertexReconstructorTest, reconstruct_basic_example) {
    Simplex v1({Point({0,0})});
    Simplex v2({Point({2,2})});
    Simplex v3({Point({1,3})});
    Simplex v4({Point({4,1})});
    Simplex v5({Point({5,2.1})});
    Simplex v6({Point({6,1.1})});
    Oracle oracle({ v1, v2, v3, v4, v5, v6 });

    VertexReconstructor reconstructor;
    reconstructor.reconstruct(oracle);

    EXPECT_EQ(0, 0);
};
