#ifndef _ORACLE_H_
#define _ORACLE_H_

#include <iostream>

#include "ctag/types.h"

#include "ctag/diagram.h"
#include "ctag/height_function.h"
#include "ctag/filtration_factory.h"
#include "ctag/diagram_factory.h"
#include "ctag/constructor.h"

namespace ctag {

class Oracle {
protected:
    typedef ctag::Types Types;

public:
    typedef Types::Coordinate Coordinate;
    typedef Types::Point Point;
    typedef Types::Direction Direction;
    typedef Types::Simplex Simplex;
    typedef Types::SimplicialComplex SimplicialComplex;
    typedef ctag::Diagram Diagram;

protected:
    typedef Types::CompTopology CompTopology;
    typedef CompTopology::Filtration Filtration;
    typedef ctag::HeightFunction<Simplex, Direction> HeightFunction;
    typedef ctag::FiltrationFactory<HeightFunction, Filtration> FiltrationFactory;
    typedef ctag::DiagramFactory<CompTopology> DiagramFactory;
    typedef ctag::Constructor Constructor;

    typedef std::vector<Point> Points;

    SimplicialComplex _simplices;

protected:
    FiltrationFactory make_filtration_factory() const { return FiltrationFactory(); }
    DiagramFactory make_diagram_factory() const { return DiagramFactory(); }

    template <typename InputIter>
    Points sorted_points(InputIter begin, InputIter end) const {
        Points points;
        for (InputIter s = begin ; s != end ; ++s) {
            for (int i = 0 ; i < s->size() ; ++i) {
                points.push_back((*s)[i]);
            }
        }
        std::sort(points.begin(), points.end());

        auto last = std::unique(points.begin(), points.end());
        points.erase(last, points.end());

        return points;
    }

    template <typename Vertex>
    bool vert_equal(const Vertex& p, const Vertex& q) const {
        return Constructor::point_eq(p, q);
    }


    template <typename InputIter>
    bool verts_equal(InputIter begin, InputIter end,
            InputIter other_begin, InputIter other_end) const {
        Points my_pts = sorted_points(begin, end);
        Points other_pts = sorted_points(other_begin, other_end);
        return std::equal(my_pts.begin(), my_pts.end(), other_pts.begin(),
            [&](const Point& p, const Point& q) { return vert_equal(p, q); }
        );
    }

    template <typename Vertex>
    bool edge_equal(const Vertex& p1, const Vertex& p2,
            const Vertex& q1, const Vertex& q2) const {
        return (vert_equal(p1, q1) && vert_equal(p2, q2))
            || (vert_equal(p1, q2) && vert_equal(p2, q1));
    }

    template <typename Simplex>
    bool is_vertex(const Simplex& s) const {
        return s.size() == 1;
    }

    template <typename InputIter>
    bool edges_subset(InputIter begin, InputIter end,
            InputIter other_begin, InputIter other_end) const {
        bool subset = true;
        for (InputIter ei = begin ; ei != end && subset; ++ei) {
            if (is_vertex(*ei)) { continue; }

            bool found = false;
            for (InputIter ej = other_begin ; ej != other_end && !found; ++ej) {
                if (is_vertex(*ej)) { continue; }
                found = edge_equal(ei[0][0], ei[0][1], ej[0][0], ej[0][1]);
            }
            subset = subset && found;

        }
        return subset;
    }

public:
    Oracle(const std::initializer_list<Simplex>& simplices) :
        Oracle(std::begin(simplices), std::end(simplices)) {}

    template<class Iterator>
    Oracle(Iterator begin, Iterator end) : _simplices(begin, end) {}

    Diagram diagram(const Direction& d) const {
        HeightFunction f(d);

        FiltrationFactory factory = make_filtration_factory();
        Filtration filtration = factory.make_filtration(
                f, _simplices.begin(), _simplices.end());

        DiagramFactory diagram_factory = make_diagram_factory();
        Diagram diagram = diagram_factory.make_diagram(f, filtration);

        return diagram;
    }

    bool verify(const SimplicialComplex& other) const {
        auto begin = _simplices.begin();
        auto end = _simplices.end();
        auto other_begin = other.begin();
        auto other_end = other.end();
        return verts_equal(begin, end, other_begin, other_end);
            //&& edges_subset(begin, end, other_begin, other_end)
            //&& edges_subset(other_begin, other_end, begin, end);
    }
};

};

#endif

