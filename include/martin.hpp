#ifndef MARTIN_MARTIN_HPP
#define MARTIN_MARTIN_HPP

#include <string>
#include <memory>
#include <peglib.h>

namespace Martin {

    std::string ReadFile(const std::string& path);
    std::shared_ptr<peg::Ast> CreateASTFromCode(const std::string& code, bool optimize=true);

}

#endif