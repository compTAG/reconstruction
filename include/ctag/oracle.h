#ifndef _ORACLE_H_
#define _ORACLE_H_

#include <iostream>

#include <dionysus/filtration.h>
#include <dionysus/simplex.h>

#include "ctag/point.h"
#include "ctag/height_function.h"
#include "ctag/filtration_factory.h"
#include "ctag/diagram.h"
#include "ctag/diagram_factory.h"

namespace ctag {

class Oracle {
public:
    typedef float Coordinate;
    typedef ctag::Point<Coordinate, 2> Point;
    typedef Point Direction;
    typedef dionysus::Simplex<Point> Simplex;
    typedef ctag::Diagram Diagram;

protected:
    typedef dionysus::Filtration<Simplex> Filtration;
    typedef ctag::HeightFunction<Simplex, Direction> HeightFunction;
    typedef ctag::FiltrationFactory<HeightFunction, Filtration> FiltrationFactory;
    typedef ctag::DiagramFactory<HeightFunction, Filtration> DiagramFactory;
    typedef dionysus::Z2Field K;

    std::vector<Simplex> _simplices;

protected:
    FiltrationFactory make_filtration_factory() const { return FiltrationFactory(); }
    DiagramFactory make_diagram_factory() const { return DiagramFactory(); }

public:
    Oracle(const std::initializer_list<Simplex>& simplices) :
        Oracle(std::begin(simplices), std::end(simplices)) {}

    template<class Iterator>
    Oracle(Iterator begin, Iterator end) : _simplices(begin, end) {}

    Diagram diagram(const Direction& d) {
        HeightFunction f(d);

        FiltrationFactory factory = make_filtration_factory();
        Filtration filtration = factory.make_filtration(
                f, _simplices.begin(), _simplices.end());

        DiagramFactory diagram_factory = make_diagram_factory();
        Diagram diagram = diagram_factory.make_diagram(f, filtration);

        return diagram;
    }
};

};

#endif

