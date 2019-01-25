
#include <../../dionysus-src/bindings/python/pybind11/include/pybind11/pybind11.h>
namespace py = pybind11;

void init_simple(py::module&);
void init_point(py::module&);

PYBIND11_MODULE(_reconstruction, m)
{
    m.doc() = "reconstruction python bindings";

    init_simple(m);
    init_point(m);
}
