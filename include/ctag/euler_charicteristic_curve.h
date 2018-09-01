#ifndef _EULER_CHARICTERISTIC_CURVE_H_
#define _EULER_CHARICTERISTIC_CURVE_H_

#include <list>
#include <limits>
#include <cassert>

namespace ctag {

class EulerCharacteristicCurve {
public:

    /**
     * A half open interval (closed on left, open on right)
     * representing a value in the Euler characteristic curve
     */
    struct Value {
        double begin, end, value;

        Value(double begin_in, double end_in, double value_in) :
            begin(begin_in), end(end_in), value(value_in) {}
    };

protected:

    std::list<Value> _values;

public:

    typedef std::list<Value>::const_iterator const_iterator;

    EulerCharacteristicCurve() {
        double neg_inf = std::numeric_limits<double>::lowest();
        double inf = std::numeric_limits<double>::max();

        _values.push_back(Value(neg_inf, inf, 0));
    }

    void push_back(double end, double value) {
        double last_end = _values.back().end;

        // make sure that the users are increasing the end value
        // so that the intervals of the function are non-overlapping
        assert(_values.back().begin < end);

        _values.back().end = end;
        _values.back().value = value;

        _values.push_back(Value(end, last_end, value));
    }

    const_iterator begin() const { return _values.begin(); }
    const_iterator end() const { return _values.end(); }
};

};

#endif
