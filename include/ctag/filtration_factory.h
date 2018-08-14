#ifndef _FILTRATION_FACTORY_H_
#define _FILTRATION_FACTORY_H_

namespace ctag {

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
