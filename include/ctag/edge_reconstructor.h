#ifndef _EDGE_RECONSTRUCTOR_H_
#define _EDGE_RECONSTRUCTOR_H_

#include <iostream>

#include "ctag/constructor.h"
#include "ctag/edge_predicate.h"

namespace ctag {

template<class Oracle_>
class EdgeReconstructor {
protected:
    typedef Oracle_ Oracle;
    typedef ctag::EdgePredicate<Oracle> EdgePredicate;

    template <class InputIter>
    double get_bowtie_angle(InputIter verts_begin, InputIter verts_end) const {
        double min = Constructor::max_angle();
        for (InputIter vi = verts_begin ; vi != verts_end ; ++vi) {
            double cur_min = Constructor::min_angle(vi, vi+1, verts_end);
            min = std::min(min, cur_min);
        }
        return min;
    }




public:
    template <class OutputIter, class InputIter>
    void reconstruct(OutputIter out, const Oracle& oracle,
            InputIter verts_begin, InputIter verts_end) const {

        typedef std::pair< InputIter, InputIter > Edge;

        double bowtie_angle = get_bowtie_angle(verts_begin, verts_end);
        assert(bowtie_angle > 1e-6);
        EdgePredicate is_edge(bowtie_angle);

        for (InputIter vi = verts_begin ; vi != verts_end ; ++vi) {
            for (InputIter vj = vi+1 ; vj != verts_end ; ++vj) {
                if (is_edge(oracle, *vi, *vj)) {
                    *out++ = Edge(vi, vj);
                }
            }
        }
    }
};
};

#endif

