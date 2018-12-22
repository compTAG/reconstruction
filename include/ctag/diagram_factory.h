#ifndef _DIAGRAM_FACTORY_H_
#define _DIAGRAM_FACTORY_H_

#include <dionysus/fields/z2.h>
#include <dionysus/ordinary-persistence.h>
#include <dionysus/standard-reduction.h>

#include "ctag/height_function.h"


namespace ctag {

template< class HeightFunction_, class Filtration_ >
class DiagramFactory {

protected:
    typedef dionysus::Z2Field Field;
    typedef dionysus::OrdinaryPersistence<Field> Persistence;
    typedef dionysus::StandardReduction<Persistence> PersistenceReducer;

    typedef HeightFunction_ HeightFunction;
    typedef typename HeightFunction::Range HeightFunctionRange;
    typedef Filtration_ Filtration;

    Field _k;

public:

    DiagramFactory() : _k(Field()) {}

    Diagram make_diagram(const HeightFunction& f,
            const Filtration& filtration) {

        Diagram diagram;

        Persistence persistence(_k);
        PersistenceReducer reduce(persistence);
        reduce(filtration);

        HeightFunctionRange inf =
            std::numeric_limits<HeightFunctionRange>::max();

        typedef decltype(persistence.pair(0)) Index;
        for (Index i = 0; i < persistence.size(); ++i) {
            Index j = persistence.pair(i);
            if (j < i) continue;

            int dim = filtration[i].dimension();
            auto birth = f(filtration[i]);
            auto death = (j == persistence.unpaired()) ? inf : f(filtration[j]);

            diagram.push_back(birth, death, dim);
        }

        return diagram;
    }
};
};

#endif
