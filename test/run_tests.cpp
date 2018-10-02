#include "gtest/gtest.h"

#include "test_height_function.cc"
#include "test_filtration_factory.cc"
#include "test_euler_charicteristic_curve.cc"
#include "test_finite_persistent_homology_transform.cc"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
