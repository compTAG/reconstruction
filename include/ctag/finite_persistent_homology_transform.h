#ifndef _FINITE_PERSISTENT_HOMOLOGY_TRANSFORM_H__
#define _FINITE_PERSISTENT_HOMOLOGY_TRANSFORM_H__

#include <vector>
#include <array>


namespace ctag {

/** todolist:
 * - DONE Set up data structure for a single pair
 * - DONE Test constructor for single pair
 * - DONE Set up data structure for a Diagram that inherits a vector class
 *   - TODO Ask dave if I should define these all individually (i.e recreate the wheel)
 * - DONE Test data structure for single Diagram
 * - DONE Set up data structure for PHT
 *   - TODO Set up FPHT to be of proper size given a given complex with n vertices
 * - DONE Test data structure for PHT
 * */

class FinitePersistentHomologyTransform {
public:

    struct Pair {
        double birth, death;

      // Constructor that gives default values as zero
        Pair(double birth_in=0, double death_in=0) :
            birth(birth_in), death(death_in) {}
    };

  struct Diagram : std::vector<Pair> {
        Diagram() {}
      };

  struct FPHT : std::vector<Diagram> {
    FPHT() {}
  };

protected:


private:

};
};

#endif
