

#include <sstream>

#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/pybind11.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/stl.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/operators.h>
namespace py = pybind11;

#include "reconstruction_tester.h"

void init_reconstruction_tester(py::module& m)
{
    using namespace pybind11::literals;

    py::class_<PyReconstructionTester>(m, "Reconstruct", "an abstract `test` class")
        .def(py::init<std::vector<double>, std::vector<int>>(), "initialize simple test class object")
    ;
}



