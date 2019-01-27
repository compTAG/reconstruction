#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/vertex_reconstructor.h"

class VertexReconstructorTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Direction Direction;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::Complex Complex;

    typedef ctag::VertexReconstructor<Oracle> VertexReconstructor;
    typedef VertexReconstructor::Vertices Vertices;
};

TEST_F(VertexReconstructorTest, reconstruct_basic_example) {
    Complex simplices = {
        Simplex({Point({0,0})}),
        Simplex({Point({2,2})}),
        Simplex({Point({1,3})}),
        Simplex({Point({4,1})}),
        Simplex({Point({5,2.1})}),
        Simplex({Point({6,1.1})})
    };
    Oracle oracle(simplices.begin(), simplices.end());

    VertexReconstructor reconstructor;
    Vertices verts = reconstructor.reconstruct(oracle);

    EXPECT_EQ(simplices.size(), verts.size());

    // for each vertex, we check if the vertex is in the initial simplex set.
    // if we find it in the set, we remove it from the simplex set.
    // Since we know:
    // 1. the number of verts and simplicies are the same (previous test)
    // 2. each vertex is "close enough" to a unique vertex in the simplex set
    // all verts have been found
    double eps = .0001;
    for (auto v : verts) {
        auto result = find_if(simplices.begin(), simplices.end(),
            [&](const Simplex& s) { return v.dist(*(s.begin())) < eps; }
        );
        EXPECT_NE(simplices.end(), result);
        simplices.erase(result);
    }
};
