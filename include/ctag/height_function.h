#ifndef _HEIGHT_FUNCTION_H_
#define _HEIGHT_FUNCTION_H_

#include <unordered_map>

namespace ctag {

template<typename Simplex_, typename Direction_>
class HeightFunction {

public:
    typedef Simplex_ Simplex;
    typedef Direction_ Direction;
    typedef typename Simplex::Vertex Vertex;
    typedef typename Vertex::Coordinate Coordinate;
    typedef Coordinate Range;

private:
    Direction _direction;
    mutable std::unordered_map<Simplex, Range> _cache;

    Range max_facet_val(const Simplex& s) const {
        Range max_val = -1.0/0.0;
        for (auto sb : s.boundary()) {
            max_val = std::max(max_val, (*this)(sb));
        }
        return max_val;
    }

    Range vert_val(const Vertex& v) const {
        return v*_direction;
    }

public:
    HeightFunction(const Direction &d) : _direction(d) {}

    Range operator()(const Simplex &s) const {
        Range simplex_value = 0;

        auto value = _cache.find(s);
        if (value != _cache.end()) {
            simplex_value = value->second;
        } else {
            simplex_value = (s.dimension() == 0) ?  vert_val(s[0]) : max_facet_val(s);
            _cache[s] = simplex_value;
        }
        return simplex_value;
    }

    Direction direction() const { return _direction; }
};

};

#endif
