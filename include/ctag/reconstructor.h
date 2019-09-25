#ifndef _RECONSTRUCTOR_H_
#define _RECONSTRUCTOR_H_

#include <iostream>
#include "ctag/oracle.h"
#include "ctag/vertex_reconstructor.h"
#include "ctag/edge_reconstructor.h"

namespace ctag {

template<class Oracle_>
class Reconstructor {
protected:
    typedef Oracle_ Oracle;
    typedef typename Oracle::Simplex Simplex;

    typedef ctag::VertexReconstructor<Oracle> VertexReconstructor;
    typedef typename VertexReconstructor::Vertices Vertices;

    typedef typename Vertices::iterator PIter;
    typedef std::pair< PIter, PIter> Edge;
    typedef std::vector< Edge > Edges;
    typedef ctag::EdgeReconstructor<Oracle> EdgeReconstructor;

public:
    template <class OutputIter>
    std::vector<double> reconstruct(OutputIter out, const Oracle& oracle) const {
        Timer t;
        oracle.timer_reset();
        t.start();

        Vertices verts;
        VertexReconstructor vert_reconstructor;
        vert_reconstructor.reconstruct(std::back_inserter(verts), oracle);

        for (auto v : verts) {
            *out++ = Simplex({v});
        }

        t.stop();
        double vert_time = t.total() - oracle.timer_total();
        t.reset();
        oracle.timer_reset();
        t.start();

        Edges edges;
        EdgeReconstructor edge_reconstructor;
        edge_reconstructor.reconstruct(std::back_inserter(edges),
                oracle, verts.begin(), verts.end());

        for (auto edge : edges) {
            *out++ = Simplex({*edge.first, *edge.second});
        }

        t.stop();
        double edge_time = t.total() - oracle.timer_total();
        return { vert_time, edge_time };
    }
};
};

#endif

