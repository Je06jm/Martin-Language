#ifndef MARTIN_VISIBILITY
#define MARTIN_VISIBILITY

#include "parse.hpp"

#include <vector>
#include <string>

namespace Martin {

    class Visibility {
    public:
        Visibility(Tree tree);

        const std::vector<TokenNode> GetFunctions(const std::string& name = "") const;
        const std::vector<TokenNode> GetTypes(const std::string& name = "") const;
        const std::vector<TokenNode> GetVariables(const std::string& name = "") const;
        const std::vector<TokenNode> GetClasses(const std::string& name = "") const;
        const std::vector<TokenNode> GetImports(const std::string& name = "") const;

    private:
        std::vector<TokenNode> functions;
        std::vector<TokenNode> types;
        std::vector<TokenNode> variables;
        std::vector<TokenNode> classes;
        std::vector<TokenNode> imports;
    };

}

#endif