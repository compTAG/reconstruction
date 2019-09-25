#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/vertex_reconstructor.h"

#include "ctag/benchmarker.h"

class BenchmarkerTest : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef ctag::VertexReconstructor<Oracle> VertexReconstructor;
    typedef typename VertexReconstructor::Vertices Vertices;

    typedef Oracle::Point Point;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::SimplicialComplex SimplicialComplex;

    typedef ctag::Benchmarker<Oracle> Benchmarker;
};

TEST_F(BenchmarkerTest, benchmark) {
    Benchmarker benchmarker([](const Oracle &o) {
        Vertices verts;
        VertexReconstructor vert_reconstructor;
        vert_reconstructor.reconstruct(std::back_inserter(verts), o);
    });


    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});

    Simplex t_e1({p1, p2});
    Simplex t_e2({p2, p3});
    Simplex t_e3({p3, p1});
    Simplex e1({p2, p4});
    Oracle oracle({ t_e1, t_e2, t_e3, e1 });

    double time = benchmarker.benchmark(oracle, 10);
    EXPECT_LT(0, time);
}
