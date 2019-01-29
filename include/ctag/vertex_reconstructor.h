#ifndef _VERTEX_RECONSTRUCTOR_H_
#define _VERTEX_RECONSTRUCTOR_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "ctag/filtration_line.h"
#include "ctag/filtration_line_factory.h"
#include "ctag/constructor.h"

namespace ctag {

template<class Oracle_>
class VertexReconstructor {
protected:
    typedef Oracle_ Oracle;
    typedef typename Oracle::Coordinate Coordinate;
    typedef typename Oracle::Direction Direction;
    typedef typename Oracle::Diagram Diagram;
    typedef typename Diagram::Pair Pair;

    typedef ctag::FiltrationLine<Direction> FiltrationLine;
    typedef ctag::FiltrationLineFactory<FiltrationLine, Diagram> FiltrationLineFactory;
    typedef std::vector<FiltrationLine> FiltrationLines;

    typedef typename Oracle::Point Point;
    typedef typename Oracle::Simplex Simplex;

public:
    typedef typename std::vector<Point> Vertices;

    void fill_filtration_lines(FiltrationLines& lines,
            const Diagram &diagram) const {
        FiltrationLineFactory factory;
        factory.make_filtration_lines(std::back_inserter(lines), diagram);
    }

    double get_width(const Oracle& oracle) const {
        Direction d1({1,0});
        Diagram diagram = oracle.diagram(d1);
        auto minmax = std::minmax_element(diagram.begin(0), diagram.end(0),
            [](const Pair& p1, const Pair& p2) { return p1.birth < p2.birth; }
        );
        double min = minmax.first->birth;
        double max = minmax.second->birth;

        return max - min;
    }

    double get_height(FiltrationLines& lines, const Oracle& oracle) const {
        Direction d2({0,1});
        Diagram diagram = oracle.diagram(d2);

        std::vector<double> births;
        std::transform(diagram.begin(0), diagram.end(0), std::back_inserter(births),
            [](const Pair &p) { return p.birth; }
        );
        std::sort(births.begin(), births.end());

        std::vector<double> diff;
        std::adjacent_difference(births.begin(), births.end(), std::back_inserter(diff));

        fill_filtration_lines(lines, diagram);
        double min = *std::min_element(diff.begin()+1, diff.end());
        return min;
    }

    Direction get_direction(double width, double height) const {
        double w = width;
        double h = height / 2;
        double norm = sqrt(w*w + h*h);
        return Direction({ -height/norm, width/norm });
    }

    void filtration_lines_for_direction(FiltrationLines& lines,
            const Oracle& oracle, const Direction& direction) const {
        Diagram diagram = oracle.diagram(direction);
        fill_filtration_lines(lines, diagram);
    }

    Vertices make_vertices(
            const FiltrationLines& lines1,
            const FiltrationLines& lines3) const {
        Vertices vertices;

        assert(lines1.size() == lines3.size());
        for (int i = 0 ; i < lines1.size() ; ++i) {
            FiltrationLine l1 = lines1[i];
            FiltrationLine l3 = lines3[i];

            Point p = Constructor::intersect(l1, l3);
            vertices.push_back(p);
        }

        return vertices;
    }

public:

    Vertices reconstruct(const Oracle& oracle) const {
        FiltrationLines lines1;
        double width = get_width(oracle);
        double height = get_height(lines1, oracle);
        Direction d3 = get_direction(width, height);

        FiltrationLines lines3;
        filtration_lines_for_direction(lines3, oracle, d3);

        Vertices vertices = make_vertices(lines1, lines3);
        return vertices;
    }
};

};

#endif
