#ifndef _FILTRATION_LINE_H_
#define _FILTRATION_LINE_H_

#include <iostream>

namespace ctag {

template<class Direction_>
class FiltrationLine {
public:
    typedef Direction_ Direction;
    typedef typename Direction::Coordinate Coordinate;

protected:
    Coordinate _a, _b, _c;

public:

    FiltrationLine() : _a(0), _b(1), _c(1) { }
    FiltrationLine(const Direction& d, const Coordinate& scale)
        : _a(d[0]), _b(d[1]), _c(-scale) {}

    Coordinate a() const { return _a; }
    Coordinate b() const { return _b; }
    Coordinate c() const { return _c; }

    friend
    std::ostream& operator<<(std::ostream& out, const FiltrationLine& l) {
        out << l.a() << "x + " << l.b() << "y + " << l.c() << " = 0";
        return out;
    }
};

};

#endif
