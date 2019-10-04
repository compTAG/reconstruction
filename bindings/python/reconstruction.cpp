
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ctag/types.h"
#include "ctag/constructor.h"
#include "ctag/compiler_stats.h"

namespace py = pybind11;

void init_reconstruction_runner(py::module&);

double min_angle(std::vector<double> coords) {
    typedef ctag::Types Types;
    typedef Types::Point Point;
    typedef ctag::Constructor Constructor;

    std::vector<Point> points = Constructor::points(coords.begin(), coords.end());
    return Constructor::get_bowtie_angle(points.begin(), points.end());
}


std::string compiler_version() {
    ctag::CompilerStats stats;
    return stats.version();
}


PYBIND11_MODULE(_reconstruction, m)
{
    m.doc() = "reconstruction python bindings";
    m.def("min_angle", &min_angle, "Get min angle from a list of points");
    m.def("compiler_version", &compiler_version, "Get the compiler version that built the library");

    init_reconstruction_runner(m);
}
