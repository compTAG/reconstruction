#ifndef _EDGE_PREDICATE_H_
#define _EDGE_PREDICATE_H_

#include <iostream>

#include "ctag/oracle.h"

namespace ctag {

template<class Oracle_>
class EdgePredicate {
protected:
    typedef Oracle_ Oracle;

    typedef typename Oracle::Direction Direction;
    typedef typename Oracle::Point Point;

    double _bowtie_angle;

public:
    EdgePredicate(double bowtie_angle) : _bowtie_angle(bowtie_angle) {}

    bool operator()(const Oracle& oracle, const Point& p, const Point& q) const {

        std::pair<Direction, Direction> directions =
            Constructor::bowtie_directions(_bowtie_angle, p, q);

        Diagram diagram = oracle.diagram(directions.first);
        int in_degree1 = Constructor::in_degree(diagram, p);

        diagram = oracle.diagram(directions.second);
        int in_degree2 = Constructor::in_degree(diagram, p);

        int diff = std::abs(in_degree2 - in_degree1);
        std::cout << diff << std::endl;
        assert(diff <= 1);

        return diff > 0;
    }
};
};

#endif

