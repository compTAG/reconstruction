#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/vertex_reconstructor.h"
#include "ctag/constructor.h"

class VertexReconstructorTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Direction Direction;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::SimplicialComplex SimplicialComplex;

    typedef ctag::VertexReconstructor<Oracle> VertexReconstructor;
    typedef VertexReconstructor::Vertices Vertices;

    typedef ctag::Constructor Constructor;
};

TEST_F(VertexReconstructorTest, reconstruct_basic_example) {
    SimplicialComplex simplices = {
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
    // 1. the number of verts and simplices are the same (previous test)
    // 2. each vertex is "close enough" to a unique vertex in the simplex set
    // all verts have been found
    for (auto v : verts) {
        auto result = find_if(simplices.begin(), simplices.end(),
            [&](const Simplex& s) { return Constructor::point_eq(v, s[0]); }
        );
        EXPECT_NE(simplices.end(), result);
        simplices.erase(result);
    }
};

TEST_F(VertexReconstructorTest, reconstruct_simple_numerical_error) {

    SimplicialComplex simplices = {
        Simplex({ Point({1,4}) }),
        Simplex({ Point({12,45}) }),
        Simplex({ Point({23,13}) })
    };
    Oracle oracle(simplices.begin(), simplices.end());

    VertexReconstructor reconstructor;
    Vertices verts = reconstructor.reconstruct(oracle);

    EXPECT_EQ(simplices.size(), verts.size());

    // for each vertex, we check if the vertex is in the initial simplex set.
    // if we find it in the set, we remove it from the simplex set.
    // Since we know:
    // 1. the number of verts and simplices are the same (previous test)
    // 2. each vertex is "close enough" to a unique vertex in the simplex set
    // all verts have been found
    for (auto v : verts) {
        auto result = find_if(simplices.begin(), simplices.end(),
            [&](const Simplex& s) { return Constructor::point_eq(v, s[0]); }
        );
        EXPECT_NE(simplices.end(), result);
        simplices.erase(result);
    }
};


TEST_F(VertexReconstructorTest, reconstruct_numerical_error01) {
    SimplicialComplex simplices = {
        Simplex({ Point({ 22.10453632616526, 6.5075439057193485 }) }),
        Simplex({ Point({ 68.62220852374669, 29.47444647173656, }) }),
        Simplex({ Point({ 16.713920310005626, 28.79344409672464, }) }),
        Simplex({ Point({ 39.244246646503065, 82.2466339103433, }) }),
        Simplex({ Point({ 61.805234725280926, 62.61830379602461, }) }),
        Simplex({ Point({ 41.1930094858746, 11.047771391367379, }) }),
        Simplex({ Point({ 0.2464881200886171, 0.052881116927605554, }) }),
        Simplex({ Point({ 88.40321823721048, 94.21662328554996, }) }),
        Simplex({ Point({ 88.49475383764735, 14.150075772518978, }) }),
        Simplex({ Point({ 30.040968936648092, 42.15965261661597, }) }),
        Simplex({ Point({ 58.958186521471454, 34.64894401485442, }) }),
        Simplex({ Point({ 97.8426916014831, 86.97850843971815, }) }),
        Simplex({ Point({ 84.50938221263111, 42.86018123522864 }) })
    };

    Oracle oracle(simplices.begin(), simplices.end());

    VertexReconstructor reconstructor;
    Vertices verts = reconstructor.reconstruct(oracle);

    EXPECT_EQ(simplices.size(), verts.size());

    // for each vertex, we check if the vertex is in the initial simplex set.
    // if we find it in the set, we remove it from the simplex set.
    // Since we know:
    // 1. the number of verts and simplices are the same (previous test)
    // 2. each vertex is "close enough" to a unique vertex in the simplex set
    // all verts have been found
    for (auto v : verts) {
        auto result = find_if(simplices.begin(), simplices.end(),
            [&](const Simplex& s) { return Constructor::point_eq(v, s[0]); }
        );
        EXPECT_NE(simplices.end(), result);
        simplices.erase(result);
    }
}
