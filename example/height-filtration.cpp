#include <iostream>
#include <unordered_map>

#include <dionysus/simplex.h>
#include <dionysus/filtration.h>
#include <dionysus/fields/z2.h>
#include <dionysus/ordinary-persistence.h>
#include <dionysus/standard-reduction.h>

#include "point.h"
#include "height_filtration.h"

typedef float Coordinate;
typedef grid::Point<Coordinate, 2> Point;
typedef Point Direction;
typedef dionysus::Z2Field K;
typedef dionysus::Simplex<Point> Simplex;
typedef dionysus::Filtration<Simplex> Filtration;
typedef dionysus::OrdinaryPersistence<K> Persistence;
typedef dionysus::StandardReduction<Persistence> PersistenceReducer;

typedef HeightFiltrationFactory<Simplex, Direction, Filtration> HeightFiltFactory;
typedef HeightFiltFactory::FilterFun HeightFilterFun;
typedef HeightFilterFun::Range HeightFilterFunRange;

void print_section(const std::string& section_name) {
    std::cout << "########################################" << std::endl;
    std::cout << "# " << section_name << std::endl;
    std::cout << "########################################" << std::endl;
}

Filtration make_filtration(const K& k, const HeightFiltFactory& hff) {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});
    Point p5({5,2});
    Point p6({6,1});

    Simplex t({p1, p2, p3});
    Simplex e1({p2, p4});
    Simplex e2({p4, p6});
    Simplex e3({p6, p5});
    Simplex e4({p5, p4});

    Filtration filtration = hff({ t, e1, e2, e3, e4 });

    print_section("Filtration");
    for (auto& s : filtration) {
        std::cout << s << " " <<  filtration.index(s) << std::endl;
        for (auto sb : s.boundary(k)) {
            std::cout << "   " << sb.element() << " * "
                <<  sb.index() << " at "
                << filtration.index(sb.index()) << std::endl;
        }
    }

    return filtration;
}

Persistence compute_persistence(const K& k, const Filtration& filtration,
        const HeightFiltFactory& hff) {
    Persistence persistence(k);
    PersistenceReducer reduce(persistence);
    reduce(filtration);

    HeightFilterFun filter_fun = hff.create_filter_fun();
    HeightFilterFunRange inf = std::numeric_limits<HeightFilterFunRange>::max();

    print_section("Persistence");
    typedef decltype(persistence.pair(0)) Index;
    for (Index i = 0; i < persistence.size(); ++i) {
        Index j = persistence.pair(i);
        if (j < i) continue;

        int dim = filtration[i].dimension();
        auto birth = filter_fun(filtration[i]);
        auto death = (j == persistence.unpaired())
            ? inf : filter_fun(filtration[j]);

        std::cout << dim << ": (" << birth << ", " << death << ")" << std::endl;
    }

    return persistence;
}



int main() {
    K k;
    Direction d({1,0});
    HeightFiltFactory hff(d);

    Filtration filtration = make_filtration(k, hff);
    compute_persistence(k, filtration,
            hff);
}
