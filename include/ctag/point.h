#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <array>
#include <cmath>

// adapted and stripped down version of point from Dionysus
namespace ctag {

template<class Coordinate_, unsigned D>
class Point: public std::array<Coordinate_, D> {
public:
    typedef Coordinate_ Coordinate;
    typedef std::array<Coordinate, D> ArrayParent;

    Point() { for (unsigned i = 0; i < D; ++i) (*this)[i] = 0; }
    Point(const ArrayParent& a): ArrayParent(a) {}
    template<class T>
    Point(const Point<T, D>& p) {
        for (size_t i = 0; i < D; ++i) { (*this)[i] = p[i]; }
    }

    unsigned dim() const { return D; }

    using ArrayParent::operator[];

    bool operator<(const Point& p) const {
        size_t i = 0;
        while (i < D && (*this)[i] == p[i]) { ++i; }
        return (*this)[i] < p[i];
    }

    friend
    std::ostream& operator<<(std::ostream& out, const Point& p) {
        out << p[0];
        for (unsigned i = 1; i < D; ++i) {
            out << " " << p[i];
        }
        return out;
    }

    friend
    Coordinate operator*(const Point& x, const Point& y) {
        Coordinate n = 0;
        for (size_t i = 0; i < D; ++i) {
            n += x[i] * y[i];
        }
        return n;
    }
};

}

#endif
