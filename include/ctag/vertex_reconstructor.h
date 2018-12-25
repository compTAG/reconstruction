#ifndef _VERTEX_RECONSTRUCTOR_H_
#define _VERTEX_RECONSTRUCTOR_H_

#include <iostream>
#include <algorithm>
#include <numeric>

namespace ctag {

template<class Oracle_>
class VertexReconstructor {
protected:
    typedef Oracle_ Oracle;
    typedef typename Oracle::Coordinate Coordinate;
    typedef typename Oracle::Direction Direction;
    typedef typename Oracle::Diagram Diagram;
    typedef typename Diagram::Pair Pair;

    typedef typename Oracle::Point Point;
    typedef typename Oracle::Simplex Simplex;

public:
    typedef typename std::vector<Simplex> Vertices;

    double get_width(Diagram &diagram, const Oracle& oracle) const {
        Direction d1({1,0});
        diagram = oracle.diagram(d1);
        auto minmax = std::minmax_element(diagram.begin(0), diagram.end(0),
            [](const Pair& p1, const Pair& p2) { return p1.birth < p2.birth; }
        );
        double min = minmax.first->birth;
        double max = minmax.second->birth;

        // FiltrationLineFactory factory(diagram, d1);
        // factory.make_lines()

        return max - min;
    }

    double get_height(const Oracle& oracle) const {
        Direction d2({0,1});
        Diagram diagram = oracle.diagram(d2);

        std::vector<double> births;
        std::transform(diagram.begin(0), diagram.end(0), std::back_inserter(births),
            [](const Pair &p) { return p.birth; }
        );
        std::sort(births.begin(), births.end());

        std::vector<double> diff;
        std::adjacent_difference(births.begin(), births.end(), std::back_inserter(diff));

        double min = *std::min_element(diff.begin()+1, diff.end());
        return min;
    }

    Direction get_direction(double width, double height) const {
        double x = width;
        double y = height;
        double norm = width*width + height*height;
        return Direction({
            static_cast<float>(width/norm),
            static_cast<float>(height/norm)
        });
    }

    // Vertices get_vertices(const Oracle& oracle,
    //         const Diagram& dgm1, const Direction& d3) {
    //     Diagram dgm3 = oracle.diagram(d3);
    //
    //     Vertices vertices;
    //
    //     return vertices;
    // }

public:

    Vertices reconstruct(const Oracle& oracle) const {
        Diagram dgm1;
        double width = get_width(dgm1, oracle);
        std::cout << width << std::endl;

        double height = get_height(oracle);
        std::cout << height << std::endl;

        Direction d3 = get_direction(width, height);
        std::cout << d3 << std::endl;

        Vertices vertices;
        // = get_vertices(oracle, dgm1, d3);
        return vertices;
    }

};

};

#endif
