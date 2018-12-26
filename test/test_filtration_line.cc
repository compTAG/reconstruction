#include <gtest/gtest.h>

#include "ctag/types.h"
#include "ctag/filtration_line.h"

class FiltrationLineTest : public ::testing::Test {
public:
    typedef ctag::Types::Direction Direction;
    typedef ctag::FiltrationLine<Direction> FiltrationLine;
};

TEST_F(FiltrationLineTest, constructor) {

    FiltrationLine lx(Direction({1,0}), 3);
    EXPECT_EQ(1, lx.a());
    EXPECT_EQ(0, lx.b());
    EXPECT_EQ(-3, lx.c());

    FiltrationLine ly(Direction({0,1}), -2);
    EXPECT_EQ(0, ly.a());
    EXPECT_EQ(1, ly.b());
    EXPECT_EQ(2, ly.c());
};
