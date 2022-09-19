#ifndef MARTIN_VERSIONS
#define MARTIN_VERSIONS

#include <stdint.h>

namespace Martin {
    typedef struct {
        enum class Level {
            Alpha,
            Beta,
            ReleaseCandidate,
            Release
        };
        
        uint32_t major = 1;
        uint32_t minor = 0;
        uint32_t patch = 0;
        Level level = Level::Release;
    } Version;
}

#endif