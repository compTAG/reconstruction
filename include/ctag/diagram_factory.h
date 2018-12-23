#ifndef _DIAGRAM_FACTORY_H_
#define _DIAGRAM_FACTORY_H_

#include "ctag/diagram.h"

namespace ctag {

template <class CompTopology_ >
class DiagramFactory {

protected:
    typedef CompTopology_ CompTopology;
    typedef typename CompTopology::Field Field;
    typedef typename CompTopology::Persistence Persistence;
    typedef typename CompTopology::PersistenceReducer PersistenceReducer;

    Field _k;

public:

    DiagramFactory() : _k(Field()) {}

    template< class HeightFunction, class Filtration>
    Diagram make_diagram(const HeightFunction& f, const Filtration& filtration) {
        Diagram diagram;

        Persistence persistence(_k);
        PersistenceReducer reduce(persistence);
        reduce(filtration);

        typedef typename HeightFunction::Range HeightFunctionRange;
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
