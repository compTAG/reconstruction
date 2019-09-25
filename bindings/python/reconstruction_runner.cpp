#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
namespace py = pybind11;

#include "reconstruction_runner.h"

void init_reconstruction_runner(py::module& m)
{
    using namespace pybind11::literals;

    py::class_<PyReconstructionRunner>(m, "Runner", "a runner for a reconstruction test")
        .def(py::init<std::vector<double>, std::vector<int>>(),
                "initialize simple test class object")
        .def("verify",
                &PyReconstructionRunner::verify,
                "Verifies that the reconstruction was successful")
        .def("benchmark",
                &PyReconstructionRunner::benchmark,
                "Benchmarks the amount of time to reconstruct minus time for computing diagrams")
        .def("benchmark_vertices",
                &PyReconstructionRunner::benchmark_vertices,
                "Benchmarks the amount of time to reconstruct vertices time for computing diagrams")
    ;
}



