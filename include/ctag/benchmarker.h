#ifndef _BENCHMARKER_H_
#define _BENCHMARKER_H_

#include "ctag/timer.h"

namespace ctag {

template<class Oracle_>
class Benchmarker {
protected:
    typedef Oracle_ Oracle;
    void (*_f)(const Oracle&);

public:
    Benchmarker(void (*f)(const Oracle&)) : _f(f) {}

    double benchmark(const Oracle& oracle, int num_iter = 1) {
        double time = 0;
        for (int i = 0 ; i < num_iter ; ++i) {
            Timer t;
            oracle.timer_reset();
            t.start();
            _f(oracle);
            t.stop();

            time += t.total() - oracle.timer_total();
        }
        return time;
    }
};
};
#endif
