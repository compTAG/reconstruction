#ifndef _DIAGRAM_H_
#define _DIAGRAM_H_

#include <array>
#include <vector>
#include <cassert>

namespace ctag {

class Diagram {
public:
    /**
     * Representation of a point in a persistence diagram
     */
    struct Pair {
        double birth, death;

        Pair(double birth, double death) : birth(birth), death(death) {}
    };

protected:
    typedef std::vector< Pair > DgmOfDim;
    std::array< DgmOfDim , 2 > _points;

    void assert_dim(uint dim) const {
        assert(0 <= dim && dim <= 1);
    }

public:

    typedef DgmOfDim::const_iterator dim_const_iterator;

    Diagram() {}

    void push_back(double birth, double death, uint dim) {
        assert_dim(dim);
        _points[dim].push_back(Pair(birth, death));
    }

    dim_const_iterator begin(uint dim) const {
        assert_dim(dim);
        return _points[dim].begin();
    }

    dim_const_iterator end(uint dim) const {
        assert_dim(dim);
        return _points[dim].end();
    }
};

};

#endif

