#include <gtest/gtest.h>

#include "ctag/types.h"
#include "ctag/height_function.h"

#include "ctag/filtration_factory.h"

#include "ctag/euler_characteristic_curve.h"
#include "ctag/euler_characteristic_curve_factory.h"

class EulerCharacteristicCurveFactoryTest : public ::testing::Test {
public:
    typedef ctag::Types Types;
    typedef Types::Point Point;
    typedef Types::Direction Direction;
    typedef Types::Simplex Simplex;
    typedef Types::CompTopology::Filtration Filtration;
    typedef ctag::HeightFunction<Simplex, Direction> HeightFunction;
    typedef ctag::FiltrationFactory<HeightFunction, Filtration> FiltrationFactory;
    typedef ctag::EulerCharacteristicCurve EulerCharacteristicCurve;
    typedef ctag::EulerCharacteristicCurveFactory<
        HeightFunction, Filtration> EulerCharacteristicCurveFactory;
};

TEST_F(EulerCharacteristicCurveFactoryTest, make_augmented_curve) {
    Direction d({1,0});
    HeightFunction f(d);

    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});
    Point p5({5,2});
    Point p6({6,1});

    Simplex t({p1, p2, p3});
    Simplex e1({p2, p4});
    Simplex e2({p4, p6});
    Simplex e3({p6, p5});
    Simplex e4({p5, p4});

    FiltrationFactory factory;
    Filtration filtration = factory.make_filtration(f, { t, e4, e3, e2 });

    EulerCharacteristicCurveFactory ecc_factory;
    EulerCharacteristicCurve curve = ecc_factory.make_augmented_curve(f, filtration);

    EulerCharacteristicCurve::const_iterator value = curve.begin();
    EXPECT_GT(-10000, value->begin);
    EXPECT_EQ(0, value->end);
    EXPECT_EQ(0, value->value);

    // add vertex P1
    value++;
    EXPECT_EQ(0, value->begin);
    EXPECT_EQ(1, value->end);
    EXPECT_EQ(1, value->value);

    // add vertex P3
    value++;
    EXPECT_EQ(1, value->begin);
    EXPECT_EQ(1, value->end);
    EXPECT_EQ(2, value->value);

    // add at same time add edge e_t1
    value++;
    EXPECT_EQ(1, value->begin);
    EXPECT_EQ(2, value->end);
    EXPECT_EQ(1, value->value);

    // add vertex P3
    value++;
    EXPECT_EQ(2, value->begin);
    EXPECT_EQ(2, value->end);
    EXPECT_EQ(2, value->value);
    //
    // at same time add edge e_t3
    value++;
    EXPECT_EQ(2, value->begin);
    EXPECT_EQ(2, value->end);
    EXPECT_EQ(1, value->value);

    // at same time add another edge e_t2
    value++;
    EXPECT_EQ(2, value->begin);
    EXPECT_EQ(2, value->end);
    EXPECT_EQ(0, value->value);

    // at same time add triangle t
    value++;
    EXPECT_EQ(2, value->begin);
    EXPECT_EQ(4, value->end);
    EXPECT_EQ(1, value->value);

    // add vertex P4
    value++;
    EXPECT_EQ(4, value->begin);
    EXPECT_EQ(5, value->end);
    EXPECT_EQ(2, value->value);

    // add vertex P5
    value++;
    EXPECT_EQ(5, value->begin);
    EXPECT_EQ(5, value->end);
    EXPECT_EQ(3, value->value);

    // at same time add edge e4
    value++;
    EXPECT_EQ(5, value->begin);
    EXPECT_EQ(6, value->end);
    EXPECT_EQ(2, value->value);

    // add vertex P6
    value++;
    EXPECT_EQ(6, value->begin);
    EXPECT_EQ(6, value->end);
    EXPECT_EQ(3, value->value);

    // at same time add edge e3
    value++;
    EXPECT_EQ(6, value->begin);
    EXPECT_EQ(6, value->end);
    EXPECT_EQ(2, value->value);

    // at same time add edge ee
    value++;
    EXPECT_EQ(6, value->begin);
    EXPECT_LT(10000, value->end);
    EXPECT_EQ(1, value->value);

    value++;
    EXPECT_EQ(value, curve.end());
}
