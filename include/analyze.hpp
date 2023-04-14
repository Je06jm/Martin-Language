#ifndef MARTIN_ANALYZE_HPP
#define MARTIN_ANALYZE_HPP

#include <memory>
#include <peglib.h>

namespace Martin::Syntax {

    void Analyze(std::shared_ptr<peg::Ast> ast);

}

#endif