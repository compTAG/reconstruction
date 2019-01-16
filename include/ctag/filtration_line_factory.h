#ifndef _FILTRATION_LINE_FACTORY_H_
#define _FILTRATION_LINE_FACTORY_H_

#include <iostream>

namespace ctag {

template<class FiltrationLine_, class Diagram_>
class FiltrationLineFactory {
public:
    typedef FiltrationLine_ FiltrationLine;

    typedef Diagram_ Diagram;
    typedef typename Diagram::Pair Pair;
    typedef typename Diagram::Direction Direction;

public:

    template<class InputIter>
    void make_filtration_lines(InputIter lines, const Diagram& diagram) {

        std::vector<double> births;
        std::transform(diagram.begin(0), diagram.end(0), std::back_inserter(births),
            [](const Pair &p) { return p.birth; }
        );
        std::sort(births.begin(), births.end());

        std::transform(births.begin(), births.end(), lines,
            [&](double birth) { return FiltrationLine(diagram.direction(), birth); }
        );
    }
};

};

#endif
