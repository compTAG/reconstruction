#include <gtest/gtest.h>

#include "ctag/euler_characteristic_curve.h"

class EulerCharacteristicCurveTest : public ::testing::Test {
public:
    typedef ctag::EulerCharacteristicCurve EulerCharacteristicCurve;
};

TEST_F(EulerCharacteristicCurveTest, constructor) {
    EulerCharacteristicCurve curve;

    EulerCharacteristicCurve::const_iterator value = curve.begin();
    EXPECT_GT(-10000, value->begin);
    EXPECT_LT(10000, value->end);
    EXPECT_EQ(0, value->value);
}

TEST_F(EulerCharacteristicCurveTest, push_back) {
    EulerCharacteristicCurve curve;

    curve.push_back(1, 0);
    curve.push_back(2, 3);
    curve.push_back(4, 5);

    EulerCharacteristicCurve::const_iterator value = curve.begin();
    EXPECT_GT(-10000, value->begin);
    EXPECT_EQ(1, value->end);
    EXPECT_EQ(0, value->value);

    value++;
    EXPECT_EQ(1, value->begin);
    EXPECT_EQ(2, value->end);
    EXPECT_EQ(3, value->value);

    value++;
    EXPECT_EQ(2, value->begin);
    EXPECT_EQ(4, value->end);
    EXPECT_EQ(5, value->value);

    value++;
    EXPECT_EQ(4, value->begin);
    EXPECT_LT(10000, value->end);
    EXPECT_EQ(5, value->value);

    value++;
    EXPECT_EQ(value, curve.end());
}


TEST_F(EulerCharacteristicCurveTest, push_back_assert_failed) {
    EulerCharacteristicCurve curve;

    ASSERT_DEATH({
        curve.push_back(2, 3);
        curve.push_back(1, 0);
    }, "");
}
