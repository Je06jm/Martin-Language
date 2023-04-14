#include <codegen.hpp>

#include <martin.hpp>

namespace Martin {
    
    void CodeGen::FromCode(const std::string& code) {
        auto ast = CreateASTFromCode(code);
    }
    
    void CodeGen::FromFile(const std::string& file) {
        auto code = ReadFile(file);
        return FromCode(code);
    }
}