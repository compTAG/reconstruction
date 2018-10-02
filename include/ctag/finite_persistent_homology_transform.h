#ifndef _FINITE_PERSISTENT_HOMOLOGY_TRANSFORM_H__
#define _FINITE_PERSISTENT_HOMOLOGY_TRANSFORM_H__

#include <vector>


namespace ctag {

/** todolist:
 * - DONE Set up data structure for a single pair
 * - DONE Set up testing framework for a single pair
 * - TODO Set up function to add to a single pair
 * - TODO Test function to add to a single pair
 * */

class FinitePersistentHomologyTransform {
public:

    struct Pair {
        double birth, death;

        Pair(double birth_in=0, double death_in=0) :
            birth(birth_in), death(death_in) {}
    };

protected:

    std::vector<Pair> _pairs;

private:

    typedef std::vector<Pair>::const_iterator const_iterator;

//     Diagram() {
//         _pairs.push_back(Pair(birth, death));
//     }
// 
//     void push_back(double birth, double death) {
//         _pairs.push_back(Pair(birth, death));
//     }
// TODO: Write test function for push_back function
};
};

#endif
