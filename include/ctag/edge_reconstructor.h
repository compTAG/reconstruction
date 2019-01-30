#ifndef _EDGE_RECONSTRUCTOR_H_
#define _EDGE_RECONSTRUCTOR_H_

#include <iostream>
#include <string>
#include <sstream>

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
            double cur_min = Constructor::min_angle(vi, verts_begin, verts_end);
            min = std::min(min, cur_min);
        }
        return min;
    }

    void check_angle(double angle, double tolerance=1e-6) const {
        if (angle < tolerance) {
            std::ostringstream oss;
            oss << "Bowtie angle too small " << angle;
            throw std::range_error(oss.str());
        }
    }

public:
    template <class OutputIter, class InputIter>
    void reconstruct(OutputIter out, const Oracle& oracle,
            InputIter verts_begin, InputIter verts_end) const {

        typedef std::pair< InputIter, InputIter > Edge;

        double bowtie_angle = get_bowtie_angle(verts_begin, verts_end);
        check_angle(bowtie_angle);
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

