#ifndef MARTIN_VISIBILITY
#define MARTIN_VISIBILITY

#include "parse.hpp"

#include <vector>
#include <string>

namespace Martin {

    class Visibility {
    public:
        typedef struct {
            const TokenNode id;
        } VisibilityNode;

        Visibility(Tree tree);

        const std::vector<VisibilityNode> GetFunctions(const std::string& name = "") const;
        const std::vector<VisibilityNode> GetTypes(const std::string& name = "") const;
        const std::vector<VisibilityNode> GetVariables(const std::string& name = "") const;
        const std::vector<VisibilityNode> GetClasses(const std::string& name = "") const;
        const std::vector<VisibilityNode> GetImports(const std::string& name = "") const;

    private:
        std::vector<VisibilityNode> functions;
        std::vector<VisibilityNode> types;
        std::vector<VisibilityNode> variables;
        std::vector<VisibilityNode> classes;
        std::vector<VisibilityNode> imports;
    };

}

#endif