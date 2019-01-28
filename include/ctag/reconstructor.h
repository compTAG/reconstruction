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
    void reconstruct(OutputIter out, const Oracle& oracle) const {
        VertexReconstructor vert_reconstructor;
        Vertices verts = vert_reconstructor.reconstruct(oracle);

        for (auto v : verts) {
            *out++ = Simplex({v});
        }

        Edges edges;
        EdgeReconstructor edge_reconstructor;
        edge_reconstructor.reconstruct(std::back_inserter(edges),
                oracle, verts.begin(), verts.end());

        for (auto edge : edges) {
            *out++ = Simplex({*edge.first, *edge.second});
        }
    }
};
};

#endif

