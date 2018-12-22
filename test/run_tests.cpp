#include "gtest/gtest.h"

#include "test_height_function.cc"
#include "test_filtration_line.cc"
#include "test_filtration_factory.cc"
#include "test_diagram.cc"
#include "test_euler_characteristic_curve.cc"
#include "test_euler_characteristic_curve_factory.cc"
#include "test_vertex_reconstructor.cc"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
