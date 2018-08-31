#include <gtest/gtest.h>

#include "ctag/euler_charicteristic_curve.h"

class EulerCharacteristicCurveTest : public ::testing::Test {
public:
    typedef ctag::EulerCharacteristicCurve EulerCharacteristicCurve;
};

TEST_F(EulerCharacteristicCurveTest, push_back) {

    EulerCharacteristicCurve curve;

    EulerCharacteristicCurve::const_iterator value = curve.begin();
    EXPECT_GT(-10000, value->begin);
    EXPECT_LT(10000, value->end);
    EXPECT_EQ(0, value->value);

    // curve.push_back(1, 2, 3);
    // curve.push_back(4, 5, 6);
    //
    // EulerCharacteristicCurve::const_iterator value = curve.begin();
    // EXPECT_EQ(1, value->begin);
    // EXPECT_EQ(2, value->end);
    // EXPECT_EQ(3, value->value);
    //
    // value++;
    // EXPECT_EQ(4, value->begin);
    // EXPECT_EQ(5, value->end);
    // EXPECT_EQ(6, value->value);
    //
    // value++;
    // EXPECT_EQ(value, curve.end());
}

