#ifndef _COMPUTATIONAL_TOPOLOGY_H_
#define _COMPUTATIONAL_TOPOLOGY_H_

#include <dionysus/simplex.h>
#include <dionysus/filtration.h>
#include <dionysus/fields/z2.h>
#include <dionysus/ordinary-persistence.h>
#include <dionysus/standard-reduction.h>

namespace ctag {


/** encapuslate dependecies of dionysus */
template < class Vertex >
class ComputationalTopology {
public:
    typedef dionysus::Simplex<Vertex> Simplex;
    typedef dionysus::Filtration<Simplex> Filtration;

    typedef dionysus::Z2Field Field;
    typedef dionysus::OrdinaryPersistence<Field> Persistence;
    typedef dionysus::StandardReduction<Persistence> PersistenceReducer;
};

};


#endif
