#include "gtest/gtest.h"

#include <cmath>

double foo(double x, double y) { return x + y; }

TEST(FooTest, Example) {
    EXPECT_EQ(15.0, foo(7, 8));
}

TEST(FooTest, Example2) {
    EXPECT_EQ(15.0, foo(7, 8));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
