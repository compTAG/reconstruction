#include <gtest/gtest.h>

#include <dionysus/simplex.h>
#include <dionysus/filtration.h>

#include "ctag/point.h"
#include "ctag/height_function.h"

#include "ctag/filtration_factory.h"

class FiltrationFactoryTest : public ::testing::Test {
public:
    typedef ctag::Point<double, 2> Point;
    typedef Point Direction;
    typedef dionysus::Simplex<Point> Simplex;
    typedef dionysus::Filtration<Simplex> Filtration;
    typedef ctag::HeightFunction<Simplex, Direction> HeightFunction;
    typedef ctag::FiltrationFactory<HeightFunction, Filtration> FiltrationFactory;
};

TEST_F(FiltrationFactoryTest, make_filtraton) {
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
    Filtration filtration = factory.make_filtration(f, { t, e1, e2, e3, e4 });

    auto iter = filtration.begin();
    EXPECT_EQ(v1, *iter);

    ++iter;
    EXPECT_EQ(v2, *iter);

    ++iter;
    EXPECT_EQ(et1, *iter);

    ++iter;
    EXPECT_EQ(v3, *iter);

    ++iter;
    EXPECT_EQ(et3, *iter);

    ++iter;
    EXPECT_EQ(et2, *iter);

    ++iter;
    EXPECT_EQ(t, *iter);

    ++iter;
    EXPECT_EQ(v4, *iter);

    ++iter;
    EXPECT_EQ(e1, *iter);

    ++iter;
    EXPECT_EQ(v5, *iter);

    ++iter;
    EXPECT_EQ(e4, *iter);

    ++iter;
    EXPECT_EQ(v6, *iter);

    ++iter;
    EXPECT_EQ(e2, *iter);

    ++iter;
    EXPECT_EQ(e3, *iter);

    ++iter;
    EXPECT_EQ(filtration.end(), iter);
}
