#ifndef _RECONSTRUCTION_RUNNER_H_
#define _RECONSTRUCTION_RUNNER_H_

#include <vector>

#include "ctag/oracle.h"
#include "ctag/reconstructor.h"
#include "ctag/benchmarker.h"
#include "ctag/compiler_stats.h"

namespace ctag {

class ReconstructionRunner {
private:
     typedef ctag::Oracle Oracle;
     typedef Oracle::SimplicialComplex SimplicialComplex;

     typedef ctag::Reconstructor<Oracle> Reconstructor;
     typedef ctag::VertexReconstructor<Oracle> VertexReconstructor;
     typedef typename VertexReconstructor::Vertices Vertices;

     typedef ctag::Benchmarker<Oracle> Benchmarker;

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

    std::vector<std::vector<double>> benchmark(int num_iterations) const {
        std::vector<std::vector<double>> times;

        Reconstructor reconstructor;
        for (int i = 0 ; i < num_iterations ; ++i) {
            SimplicialComplex result;
            times.push_back(
                reconstructor.reconstruct(std::back_inserter(result), _oracle)
            );
        }
        return times;
    }

    std::vector<std::vector<double>> benchmark_vertices(int num_iterations) const {
        Benchmarker benchmarker([](const Oracle &o) {
            Vertices verts;
            VertexReconstructor reconstructor;
            reconstructor.reconstruct(std::back_inserter(verts), o);
        });

        std::vector<std::vector<double>> times;
        for (int i = 0 ; i < num_iterations ; ++i) {
            double time = benchmarker.benchmark(_oracle);
            times.push_back({time, 0});
        }
        return times;
    }
};

};

#endif

#pragma once

using PyReconstructionRunner = ctag::ReconstructionRunner;
