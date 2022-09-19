#ifndef MARTIN_LAMBDA
#define MARTIN_LAMBDA

#include <parse.hpp>
#include <string>

namespace Martin {

    void ResetLambdaCounter();
    void ProcessLambdas(Tree tree, const std::string& module_name);

}

#endif