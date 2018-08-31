#ifndef _EULER_CHARICTERISTIC_CURVE_H_
#define _EULER_CHARICTERISTIC_CURVE_H_

#include <list>

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

    }

    void push_back(double begin, double end, double value) {
        _values.push_back(Value(begin, end, value));
    }

    const_iterator begin() const { return _values.begin(); }
    const_iterator end() const { return _values.end(); }




    // TODO
    // iterate over the values in the ECC
    // implement a push_back
    // add logic to pushback to throw do something if the input is wrong

};

};

#endif
