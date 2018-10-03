#include <gtest/gtest.h>

#include <dionysus/simplex.h>
#include <dionysus/filtration.h>

#include "ctag/point.h"
#include "ctag/height_function.h"

#include "ctag/filtration_factory.h"

#include "ctag/euler_characteristic_curve.h"
#include "ctag/euler_characteristic_curve_factory.h"

class EulerCharacteristicCurveFactoryTest : public ::testing::Test {
public:
    typedef ctag::Point<double, 2> Point;
    typedef Point Direction;
    typedef dionysus::Simplex<Point> Simplex;
    typedef dionysus::Filtration<Simplex> Filtration;
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

    const Simplex& et1 = *(t.boundary_begin() + 2);
    const Simplex& et2 = *(t.boundary_begin() + 1);
    const Simplex& et3 = *(t.boundary_begin());

    const Simplex& v1 = *(et1.boundary_begin() + 1);
    const Simplex& v2 = *(et1.boundary_begin());
    const Simplex& v3 = *(et2.boundary_begin());

    Simplex e1({p2, p4});
    Simplex e2({p4, p6});
    Simplex e3({p6, p5});
    Simplex e4({p5, p4});

    const Simplex& v4 = *(e1.boundary_begin());
    const Simplex& v5 = *(e4.boundary_begin());
    const Simplex& v6 = *(e2.boundary_begin());

    FiltrationFactory factory;
    Filtration filtration = factory.make_filtration(f, { t, e4, e3, e2 });

    bool augmented = true;
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
