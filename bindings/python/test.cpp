
#include <sstream>

#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/pybind11.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/stl.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/operators.h>
namespace py = pybind11;

#include "test.h"

void init_simple(py::module& m)
{
    using namespace pybind11::literals;

    py::class_<PyTest>(m, "Test", "an abstract `test` class")
        .def(py::init<>(), "initialize simple test class object")
        .def("add",  &PyTest::add, "Adds two numbers together")
    ;
}


