#include <sstream>

#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/pybind11.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/stl.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/operators.h>
namespace py = pybind11;

#include "point.h"

void init_point(py::module& m)
{
    using namespace pybind11::literals;

    py::class_<PyPoint>(m, "Point", "A single point")
        .def(py::init<>(), "initialize a point")
        //.def("__getitem__",     &PyPoint::operator[],         "i-th element of point")
        .def("__repr__",        [](const PyPoint& p) { std::ostringstream oss; oss << p; return oss.str(); })
    ;
}


