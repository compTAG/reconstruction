#ifndef _DIAGRAM_H_
#define _DIAGRAM_H_

#include <array>
#include <vector>
#include <cassert>

#include "ctag/types.h"

namespace ctag {

class Diagram {
public:
    typedef ctag::Types::Direction Direction;

    /**
     * Representation of a point in a persistence diagram
     */
    struct Pair {
        double birth, death;

        Pair(double birth, double death) : birth(birth), death(death) {}
        friend std::ostream& operator<<(std::ostream& out, const Pair& d) {
            out << "(" << d.birth << ", " << d.death << ")";
            return out;
        }
    };

protected:
    typedef std::vector< Pair > DgmOfDim;
    std::array< DgmOfDim , 2 > _points;
    Direction _direction;

    void assert_dim(uint dim) const {
        assert(0 <= dim && dim <= 1);
    }

public:

    typedef DgmOfDim::const_iterator dim_const_iterator;

    Diagram(const Direction& d) : _direction(d) {}

    void push_back(double birth, double death, uint dim) {
        assert_dim(dim);
        _points[dim].push_back(Pair(birth, death));
    }

    uint num_diagrams() const { return _points.size(); }

    Direction direction() const { return _direction; }

    dim_const_iterator begin(uint dim) const {
        assert_dim(dim);
        return _points[dim].cbegin();
    }

    dim_const_iterator end(uint dim) const {
        assert_dim(dim);
        return _points[dim].cend();
    }

    friend std::ostream& operator<<(std::ostream& out, const Diagram& d) {
        for (int i = 0 ; i < d.num_diagrams() ; ++i) {
            out << "Dimension " << i << std::endl;

            std::for_each(d.begin(i), d.end(i), [&](const Pair& pair) {
                out << "  " << pair << std::endl;
            });
        }
        return out;
    }
};

};

#endif

