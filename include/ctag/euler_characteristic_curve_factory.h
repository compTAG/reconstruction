#ifndef _EULER_CHARACTERISTIC_CURVE_FACTORY_H_
#define _EULER_CHARACTERISTIC_CURVE_FACTORY_H_

#include "ctag/euler_characteristic_curve.h"

namespace ctag {

template<typename FilterFunction_, typename Filtration_>
class EulerCharacteristicCurveFactory {
public:
    typedef FilterFunction_ FilterFunction;
    typedef Filtration_ Filtration;

public:

    EulerCharacteristicCurve make_curve(const Filtration& filtration) const {
        // auto iter = filtration.begin();
        // EXPECT_EQ(v1, *iter);

        return EulerCharacteristicCurve();
    }
};

};

#endif
