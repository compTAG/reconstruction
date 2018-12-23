#ifndef _ORACLE_H_
#define _ORACLE_H_

#include <iostream>

#include "ctag/types.h"

#include "ctag/diagram.h"
#include "ctag/height_function.h"
#include "ctag/filtration_factory.h"
#include "ctag/diagram_factory.h"

namespace ctag {

class Oracle {
protected:
    typedef ctag::Types Types;

public:
    typedef Types::Coordinate Coordinate;
    typedef Types::Point Point;
    typedef Types::Direction Direction;
    typedef Types::Simplex Simplex;
    typedef ctag::Diagram Diagram;

protected:
    typedef Types::CompTopology CompTopology;
    typedef CompTopology::Filtration Filtration;
    typedef ctag::HeightFunction<Simplex, Direction> HeightFunction;
    typedef ctag::FiltrationFactory<HeightFunction, Filtration> FiltrationFactory;
    typedef ctag::DiagramFactory<CompTopology> DiagramFactory;

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

