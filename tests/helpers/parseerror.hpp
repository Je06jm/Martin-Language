#ifndef MARTIN_HELPERS_PARSEERROR
#define MARTIN_HELPERS_PARSEERROR

#include <logging.hpp>

namespace Martin {

    std::string ParseNodeError(std::string actual, std::string given) {
        return Format("Parser node is $ when given \"$\"", actual, given);
    }

}

#endif