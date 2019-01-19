#include "gtest/gtest.h"

#include "test_height_function.cc"
#include "test_filtration_factory.cc"
#include "test_diagram.cc"
#include "test_diagram_factory.cc"
#include "test_oracle.cc"
#include "test_constructor.cc"

#include "test_filtration_line.cc"
#include "test_filtration_line_factory.cc"

#include "test_edge_predicate.cc"

#include "test_vertex_reconstructor.cc"

#include "test_euler_characteristic_curve.cc"
#include "test_euler_characteristic_curve_factory.cc"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
