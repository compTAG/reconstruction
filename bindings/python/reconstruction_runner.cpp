

#include <sstream>

#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/pybind11.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/stl.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/operators.h>
namespace py = pybind11;

#include "reconstruction_runner.h"

void init_reconstruction_runner(py::module& m)
{
    using namespace pybind11::literals;

    py::class_<PyReconstructionRunner>(m, "ReconstructionRunner", "a running for a reconstruction test")
        .def(py::init<std::vector<double>, std::vector<int>>(), "initialize simple test class object")
        .def("verify",  &PyReconstructionRunner::verify, "Verifies that the reconstruction was successful")
        .def("benchmark",  &PyReconstructionRunner::benchmark, "Benchmarks the amount of time to reconstruct minus time for computing diagrams")
    ;
}



