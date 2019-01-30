#include <iostream>

#include "ctag/oracle.h"
#include "ctag/reconstructor.h"

typedef ctag::Oracle Oracle;
typedef Oracle::Point Point;
typedef Oracle::Simplex Simplex;
typedef Oracle::SimplicialComplex SimplicialComplex;

typedef ctag::Reconstructor<Oracle> Reconstructor;

int main() {
    Point p1({0,0});
    Point p2({2,2});
    Point p3({1,3});
    Point p4({4,1});

    Simplex t_e1({p1, p2});
    Simplex t_e2({p2, p3});
    Simplex t_e3({p3, p1});
    Simplex e1({p2, p4});

    Oracle oracle({ t_e1, t_e2, t_e3, e1 });
    std::cout << "Reconstructing:" << std::endl;
    std::cout << oracle << std::endl;

    SimplicialComplex result;
    Reconstructor reconstructor;
    reconstructor.reconstruct(std::back_inserter(result), oracle);

    std::string verify = (oracle.verify(result)) ? "success" : "fail";
    std::cout << "Reconstruction " << verify << std::endl;
    std::cout << "  " << oracle.timer_total() << " ns computing diagrams" << std::endl;
    return(0);
}
