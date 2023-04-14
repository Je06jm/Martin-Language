#ifndef MARTIN_UTILS_HPP
#define MARTIN_UTILS_HPP

#include <logging.hpp>

#define internal_error Martin::Fatal("Internal error($: $)\n", __FILE__, __LINE__);

#endif