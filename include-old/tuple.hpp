#ifndef MARTIN_NODES_TUPLE
#define MARTIN_NODES_TUPLE

#include <vector>

#include "values.hpp"

namespace Martin {

    Value MakeTuple(const std::vector<Value>& values);

}

#endif