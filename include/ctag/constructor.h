#ifndef _CONSTRUCTOR_H_
#define _CONSTRUCTOR_H_

#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>

#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/vec_mat_operations.hpp>

#include <boost/qvm/map_mat_mat.hpp>

#include "ctag/types.h"
#include "ctag/diagram.h"

namespace ctag {
class Constructor {
public:
    typedef ctag::Types::Coordinate Coordinate;
    typedef ctag::Types::Point Point;
    typedef ctag::Types::Direction Direction;

protected:
    typedef boost::qvm::mat<double,2,2> Matrix;
    typedef boost::qvm::vec<double,2> Vector;

    static double det(const Matrix& m) { return boost::qvm::determinant(m); }

    constexpr static double EPS = 1e-6;
    constexpr static double CONSTRUCTION_EPS = 1e-4;

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

    template<class Point>
    static double point_eq(const Point& p1, const Point& p2) {
        return Constructor::distance(p1, p2) < CONSTRUCTION_EPS;
    }

    static double max_angle() {
        return 2*M_PI;
    }

    template<class InputIter>
    static double min_angle(InputIter v, InputIter begin, InputIter end) {
        typedef std::pair< double, Direction > PolarAngle;

        std::vector< PolarAngle > angles;
        for (InputIter vi = begin; vi != end; ++vi) {
            if (v == vi) { continue; }

            double dx = (*vi)[0] - (*v)[0];
            double dy = (*vi)[1] - (*v)[1];
            double a = std::atan(dy / dx);
            angles.push_back( PolarAngle(a, Direction({dx, dy}) ));
        }

        std::sort(angles.begin(), angles.end(),
            [](const PolarAngle& a, const PolarAngle& b) { return a.first < b.first; }
        );

        double min_theta = max_angle();

        auto vi = angles.begin();
        auto vim1 = angles.end() - 1;
        while (vi != angles.end()) {
            const Point& cur = vi->second;
            const Point& prev = (vim1)->second;

            double a_dot_b = cur * prev;
            double norm_a = sqrt(cur * cur);
            double norm_b = sqrt(prev * prev);
            double theta = std::acos(a_dot_b / (norm_a*norm_b));

            double ccw = prev[0] * cur[1] - prev[1] * cur[0];
            if (ccw < 0) {
                theta = 2*M_PI - theta;
            }
            min_theta = std::min(min_theta, theta);

            vim1 = vi;
            ++vi;
        }

        return min_theta;
    }

    static int in_degree(const Diagram& d, const Point& v) {
        double c = v * d.direction();

        int d0 = std::count_if(d.begin(0), d.end(0),
            [c](const Diagram::Pair& p) { return std::abs(p.death - c) < EPS; }
        );

        int d1 = std::count_if(d.begin(1), d.end(1),
            [c](const Diagram::Pair& p) { return std::abs(p.birth - c) < EPS; }
        );

        return d0 + d1;
    }

    static std::pair<Direction, Direction> bowtie_directions(double bowtie_angle,
            const Point& p, const Point& q) {

            Vector v = {p[0] - q[0], p[1] - q[1]};
            boost::qvm::normalize(v);

            Vector v_perp = {-boost::qvm::Y(v), boost::qvm::X(v)};

            double theta = bowtie_angle / 2.;
            Matrix rot = { cos(theta), -sin(theta), sin(theta), cos(theta) };
            Vector d1 = rot * v_perp;
            Vector d2 = transposed(rot) * v_perp;

            return std::pair<Direction, Direction>(
                    Direction({ boost::qvm::X(d1), boost::qvm::Y(d1) }),
                    Direction({ boost::qvm::X(d2), boost::qvm::Y(d2) }));

    }
};
};

#endif
