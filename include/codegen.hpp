#ifndef MARTIN_CODE_GEN
#define MARTIN_CODE_GEN

#include <string>
#include <astnode.hpp>

namespace Martin {
    
    class CodeGen {
    private:
        std::shared_ptr<ASTNode> root;
        
    public:
        void Run();
        void Compile(const std::string& path);
        
        static CodeGen FromCode(const std::string& code);
        static CodeGen FromFile(const std::string& file);
    };
    
}

#endif