#ifndef _CONSTRUCTOR_H_
#define _CONSTRUCTOR_H_

#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>

namespace ctag {
class Constructor {
public:
    typedef ctag::Types::Coordinate Coordinate;
    typedef ctag::Types::Point Point;
    typedef ctag::Types::Direction Direction;

protected:
    typedef boost::qvm::mat<double,2,2> Matrix;

    static double det(const Matrix& m) { return boost::qvm::determinant(m); }

public:

    /**
     * This function assumes that l1 and l2 are distinct and not parallel
     * Lines as distinct are not chedked.
     * */
    template<class Line>
    static Point intersect(const Line& l1, const Line& l2) {
        Matrix x = { l1.b(), l1.c(), l2.b(), l2.c() };
        Matrix y = { l1.a(), l1.c(), l2.a(), l2.c() };
        Matrix z = { l1.a(), l1.b(), l2.a(), l2.b() };

        double det_x = det(x);
        double det_y = det(y);
        double det_z = det(z);

        assert(det_z != 0);

        Point p({
            static_cast<Coordinate>(det_x/det_z),
            static_cast<Coordinate>(-det_y/det_z)
        });

        return p;
    }

    /**
     * This function assumes that l1 and l2 are distinct and not parallel
     * Lines as distinct are not chedked.
     * */
    template<class Point>
    static double distance(const Point& p1, const Point& p2) {
        double acc = 0;

        for (size_t i = 0; i < p1.dim() ; ++i) {
            double diff = p1[i] - p2[i];
            acc += diff*diff;
        }
        return std::sqrt(acc);
    }
};
};

#endif
