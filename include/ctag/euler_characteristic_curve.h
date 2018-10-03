#ifndef _EULER_CHARACTERISTIC_CURVE_H_
#define _EULER_CHARACTERISTIC_CURVE_H_

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
    bool _augmented;

public:

    typedef std::list<Value>::const_iterator const_iterator;

    EulerCharacteristicCurve(bool augmented=false) : _augmented(augmented) {
        double neg_inf = std::numeric_limits<double>::lowest();
        double inf = std::numeric_limits<double>::max();

        _values.push_back(Value(neg_inf, inf, 0));
    }

    /**
     * Construct an interval in the ECC that ends at "end" and takes the value
     * "value".  The beginning of the new interval is the end of the last finite
     * interval.
     *
     * @param end the end (exclusive) of the interval
     * @param value the value over the interval
     */
    void push_back(double end, double value) {
        double last_end = _values.back().end;

        // make sure that the users are increasing the end value
        // so that the intervals of the function are non-overlapping
        assert(_values.back().begin < end
                || (_augmented && _values.back().begin == end));

        _values.back().end = end;
        _values.back().value = value;

        _values.push_back(Value(end, last_end, value));
    }

    /**
     * Set the value for the "back" interval.
     * Taat is, the interval that
     * has positive infinity as its end
     *
     * @param value the value over the interval
     */
    void push_back(double value) {
        _values.back().value = value;
    }

    const_iterator begin() const { return _values.begin(); }
    const_iterator end() const { return _values.end(); }
};

};

#endif
