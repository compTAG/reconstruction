#ifndef _RECONSTRUCTOR_H_
#define _RECONSTRUCTOR_H_

#include <iostream>

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

