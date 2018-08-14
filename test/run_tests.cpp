#include "gtest/gtest.h"

#include "test_Setup.cc"
#include "test_height_function.cc"
#include "test_filtration_factory.cc"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
