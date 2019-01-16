#ifndef _TYPES_H_
#define _TYPES_H_

#include "ctag/point.h"
#include "ctag/computational_topology.h"

namespace ctag {

class Types {
public:
    typedef double Coordinate;
    typedef ctag::Point<Coordinate, 2> Point;
    typedef Point Direction;

    typedef ctag::ComputationalTopology<Point> CompTopology;
    typedef CompTopology::Simplex Simplex;
};
};

#endif
