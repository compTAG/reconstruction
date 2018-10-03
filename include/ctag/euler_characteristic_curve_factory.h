#ifndef _EULER_CHARACTERISTIC_CURVE_FACTORY_H_
#define _EULER_CHARACTERISTIC_CURVE_FACTORY_H_

#include <cmath>

#include "ctag/euler_characteristic_curve.h"

namespace ctag {

template<typename FilterFunction_, typename Filtration_>
class EulerCharacteristicCurveFactory {
public:
    typedef FilterFunction_ FilterFunction;
    typedef Filtration_ Filtration;

public:

    EulerCharacteristicCurve make_augmented_curve(const FilterFunction& f,
            const Filtration& filtration) const {
        EulerCharacteristicCurve ecc(true);

        int value = 0;
        for (auto& s : filtration) {
            ecc.push_back(f(s), value);
            value += std::pow(-1, s.dimension());
        }
        ecc.push_back(value);

        return ecc;
    }
};

};

#endif
