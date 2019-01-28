#ifndef _TIMER_H_
#define _TIMER_H_

#include <plf_nanotimer.h>

namespace ctag {
class Timer {
protected:

	plf::nanotimer _timer;
    double _delta;

public:
    Timer() : _delta(0) {}
    void start() { _timer.start(); }
    void stop() { _delta += _timer.get_elapsed_ns(); }
    double total() const { return _delta; }
};
};
#endif
