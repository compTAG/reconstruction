#include <sstream>

#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/pybind11.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/stl.h>
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/operators.h>
namespace py = pybind11;

#include "reconstruction_tester.h"

void init_simplex(py::module& m)
{
    using namespace pybind11::literals;

    py::class_<PySimplex>(m, "Simplex", "A simplex")
        .def(py::init([](const std::vector<PySimplex::Point>& pts)
                {
                    PySimplex* simp = new PySimplex;
                    for (auto& pt : pts)
                        simp->join(pt);
                    return simp;
                }), "initialize diagram from a list of (birth,death) points")
        //.def("__getitem__",     &PyPoint::operator[],         "i-th element of point")
    ;
}


