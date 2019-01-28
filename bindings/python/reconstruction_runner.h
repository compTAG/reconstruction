#ifndef _RECONSTRUCTION_RUNNER_H_
#define _RECONSTRUCTION_RUNNER_H_

 #include "ctag/oracle.h"
 #include "ctag/reconstructor.h"
 #include "ctag/timer.h"

#include <vector>
namespace ctag {

class ReconstructionRunner {
private:
     typedef ctag::Oracle Oracle;
     typedef Oracle::SimplicialComplex SimplicialComplex;

     typedef ctag::Reconstructor<Oracle> Reconstructor;
     typedef ctag::Timer Timer;

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
        Timer t;
        Reconstructor reconstructor;

        t.start();
        _oracle.timer_reset();
        for (int i = 0 ; i < num_iterations ; ++i) {
            SimplicialComplex result;
            reconstructor.reconstruct(std::back_inserter(result), _oracle);
        }
        t.stop();
        return t.total() - _oracle.timer_total();
    }

};

};

#endif

#pragma once

using PyReconstructionRunner = ctag::ReconstructionRunner;
