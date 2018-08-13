#ifndef _HEIGHT_FILTRATION_H_
#define _HEIGHT_FILTRATION_H_

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
};

template<typename FilterFunction_, typename Filtration_>
class FiltrationFactory {
public:
    typedef FilterFunction_ FilterFunction;
    typedef typename FilterFunction::Simplex Simplex;
    typedef Filtration_ Filtration;

private:
    void add_simplex(Filtration& f, const Simplex& s) const {
        for (auto sb : s.boundary()) {
            add_simplex(f, sb);
        }
        f.push_back(s);
    }

public:

    Filtration make_filtration(const FilterFunction& f,
            const std::initializer_list<Simplex>& simplices) const {
        return make_filtration(f, std::begin(simplices), std::end(simplices));
    }

    template<class Iterator>
    Filtration make_filtration(const FilterFunction& f,
            Iterator begin, Iterator end) const {

        Filtration filtration;
        for (Iterator it = begin ; it != end ; ++it) {
            add_simplex(filtration, *it);
        }

        filtration.sort([&f](const Simplex& s1, const Simplex& s2) {
            return f(s1) < f(s2)
                || (f(s1) == f(s2) && s1.dimension() < s2.dimension());
        });
        return filtration;
    }
};

};

#endif
