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
    bool check_general_position_assumption() const {
        int i, j, k;
        std::vector<double> x_coords;
        std::vector<Point> points;
        for(i = 0; i < _simplices.size(); i++){
            for(j = 0; j < 3; j++){
                points.push_back(_simplices[i][j]);
            }
        }
        for(k = 0; k < points.size(); k++){
            std::cout << points[k] << std::endl;
        }
        //vector<double> x_coords;
        //vector<double> y_coords;
        //vector<Point> all_points;
        return 0;
    }

public:
    Oracle(const std::initializer_list<Simplex>& x) :
        Oracle(std::begin(x), std::end(x)) {}

    template<class Iterator>
    Oracle(Iterator begin, Iterator end) : _simplices(begin, end) {
        check_general_position_assumption();
        //assert(...); 
    }

    Diagram diagram(const Direction& d) const {
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

