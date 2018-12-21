#include <gtest/gtest.h>

#include "ctag/point.h"
#include "ctag/vertex_reconstructor.h"

class VertexReconstructorTest : public ::testing::Test {
public:
    typedef ctag::Point<double, 2> Point;
    typedef Point Direction;
    typedef ctag::VertexReconstructor<Direction> VertexReconstructor;
};

TEST_F(VertexReconstructorTest, constructor) {

    VertexReconstructor vr;
    EXPECT_EQ(0, 0);
};
