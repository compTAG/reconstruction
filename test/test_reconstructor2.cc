#include <gtest/gtest.h>

#include "ctag/oracle.h"
#include "ctag/reconstructor.h"

class Reconstructor2Test : public ::testing::Test {
public:
    typedef ctag::Oracle Oracle;

    typedef Oracle::Point Point;
    typedef Oracle::Simplex Simplex;
    typedef Oracle::SimplicialComplex SimplicialComplex;

    typedef ctag::Reconstructor<Oracle> Reconstructor;
};


TEST_F(Reconstructor2Test, reconstruct_basic_example) {

        // Populate points
				std::vector<double> coords = {1,4,12,45,23,13};
				std::vector<int> edges = {0,2,1,2};
         std::vector<Point> points;
         auto coord_i = coords.begin();
         while (coord_i != coords.end()) {
             double x = *coord_i;
             ++coord_i;
             assert(coord_i != coords.end());
             double y = *coord_i;
             points.push_back(Point({x, y}));
             ++coord_i;
         }

          //Creating a vector of points (i.e. vertices) seems to work...
        for (auto p : points) { std::cout << p << std::endl; }
        std::cout << std::endl;

        // Populate simplexes
         std::vector<Simplex> simplices;
         auto edge_i = edges.begin();
         while (edge_i != edges.end()) {
             int src = *edge_i;
             ++edge_i;
             assert(edge_i != edges.end());
             double dst = *edge_i;
        
             simplices.push_back(Simplex({points[src], points[dst]}));
             ++edge_i;
         }
        
         // Presumably this worked... Need some << methods for simplices to
         // print out results and verify
         Oracle _oracle(simplices.begin(), simplices.end());

         SimplicialComplex result;
         Reconstructor reconstructor;
         reconstructor.reconstruct(std::back_inserter(result), _oracle);
         std::cout << _oracle.verify(result) << std::endl;

    EXPECT_EQ(0,0);
};
