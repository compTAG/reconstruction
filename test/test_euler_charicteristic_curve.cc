#include <gtest/gtest.h>

#include "ctag/euler_charicteristic_curve.h"

class EulerCharacteristicCurveTest : public ::testing::Test {
public:
    typedef ctag::EulerCharacteristicCurve EulerCharacteristicCurve;
};

TEST_F(EulerCharacteristicCurveTest, constructor) {

    EulerCharacteristicCurve curve(7);
    EXPECT_EQ(8, curve.my_x);

    // curve.my_x = 8;

}

