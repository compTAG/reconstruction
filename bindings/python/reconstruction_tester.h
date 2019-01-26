#ifndef _RECONSTRUCTOR_TESTER_H_
#define _RECONSTRUCTOR_TESTER_H_

// #include "ctag/oracle.h"

#include<vector>
namespace ctag {

class ReconstructionTester {
private:
    // typedef ctag::Oracle Oracle;
    // typedef Oracle::Point Point;
    // typedef Oracle::Simplex Simplex;

    // typedef ctag::Reconstructor<Oracle> Reconstructor;
    //
    // Oracle _oracle;

public:

    ReconstructionTester(std::vector<double> coords,
            std::vector<int> edges) {

        for (auto c : coords) { std::cout << c; }
        std::cout << std::endl;
        for (auto e : edges) { std::cout << e; }
        std::cout << std::endl;

        // // TODO:include point header and def point
        // std::vector<Point> points;
        // auto coord_i = coords.begin();
        // while (coord_i != coords.end()) {
        //     double x = *coord_i;
        //     ++coord_i;
        //     assert(coord_i != coords.end());
        //     double y = *coord_i;
        //     points.push_back(Point({x, y});
        //     ++coord_i;
        // }
        //
        // // TODO: include simplex
        // std::vector<Simplex> simplices;
        // auto edge_i = edges.begin();
        // while (edge_i != edges.end()) {
        //     int src = *edge_i;
        //     ++edge_i;
        //     assert(edge_i != edges.end());
        //     double dst = *edge_i;
        //
        //     simplices.push_back(Simplex({points[src], points[dst]});
        //     ++edge_i;
        // }
        //
        // _oracle = Oracle(simplices.begin(), simplices.end());
    }

    bool test() const {
        // std::vector<Simplex> result;
        // Reconstructor reconstructor;
        // reconstructor.reconstruct(std::back_inserter(result), oracle);
        //
        // return oracle.verify(result);
        return false;
    }
};

};

#endif

#pragma once

using PyReconstructionTester = ctag::ReconstructionTester;
