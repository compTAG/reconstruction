#include <gtest/gtest.h>

#include "ctag/diagram.h"

class DiagramTest : public ::testing::Test {
public:
    typedef ctag::Diagram Diagram;
};

TEST_F(DiagramTest, constructor) {
    Diagram diagram;

    EXPECT_EQ(0, 0);
};

TEST_F(DiagramTest, push_back) {
    Diagram diagram;

    diagram.push_back(0, 1, 1);
    diagram.push_back(3, 4, 0);
    diagram.push_back(4, 5, 0);
    diagram.push_back(1, 2, 1);

    Diagram::dim_const_iterator pair = diagram.begin(0);
    EXPECT_EQ(3, pair->birth);
    EXPECT_EQ(4, pair->death);

    pair++;
    EXPECT_EQ(4, pair->birth);
    EXPECT_EQ(5, pair->death);

    pair = diagram.begin(1);
    EXPECT_EQ(0, pair->birth);
    EXPECT_EQ(1, pair->death);

    pair++;
    EXPECT_EQ(1, pair->birth);
    EXPECT_EQ(2, pair->death);
};

TEST_F(DiagramTest, push_back_dim_out_of_bounds_fail) {
    Diagram diagram;

    ASSERT_DEATH({
        diagram.push_back(0, 1, 4);
    }, "");
}

TEST_F(DiagramTest, begin_dim_out_of_bounds_fail) {
    Diagram diagram;

    ASSERT_DEATH({
        diagram.begin(3);
    }, "");
}

TEST_F(DiagramTest, end_dim_out_of_bounds_fail) {
    Diagram diagram;

    ASSERT_DEATH({
        diagram.end(2);
    }, "");
}







