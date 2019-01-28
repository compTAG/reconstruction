#ifndef _RECONSTRUCTION_RUNNER_H_
#define _RECONSTRUCTION_RUNNER_H_

 #include "ctag/oracle.h"
 #include "ctag/reconstructor.h"

#include<vector>
namespace ctag {

class ReconstructionRunner {
private:
     typedef ctag::Oracle Oracle;
     typedef Oracle::SimplicialComplex SimplicialComplex;

     typedef ctag::Reconstructor<Oracle> Reconstructor;

     Oracle _oracle;

public:

    ReconstructionRunner(std::vector<double> coords, std::vector<int> edges) :
        _oracle(coords.begin(), coords.end(), edges.begin(), edges.end()) {}

    bool verify() const {
         SimplicialComplex result;
         Reconstructor reconstructor;
         reconstructor.reconstruct(std::back_inserter(result), _oracle);
         return _oracle.verify(result);
    }

    double benchmark(int num_iterations) const {
        Reconstructor reconstructor;

        for (int i = 0 ; i < num_iterations ; ++i) {
            SimplicialComplex result;
            reconstructor.reconstruct(std::back_inserter(result), _oracle);
        }
        return 1234.90889;
    }

};

};

#endif

#pragma once

using PyReconstructionRunner = ctag::ReconstructionRunner;
