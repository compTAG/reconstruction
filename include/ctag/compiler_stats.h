#ifndef COMPILER_STATS_H
#define COMPILER_STATS_H

#include <string>
#include <sstream>

namespace ctag {

class CompilerStats {
public:

    std::string version() const {
        std::ostringstream stats;
#if  defined(__clang_major__)
        stats << "CLANG verson " << __clang_major__ << "." << __clang_minor__;
#elif defined(__GNUC__)
        stats << "GCC verson " << __GNUC__ << "." <<  __GNUC_MINOR__ ;
#else
        stats << "Unknown compiler"
#endif
        return stats.str();
    }
};
}

#endif
