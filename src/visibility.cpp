#include <visibility.hpp>

namespace Martin {

    Visibility::Visibility(Tree tree) {
        for (auto token_node : (*tree)) {
            if (!token_node->is_token) {
                switch (token_node->node->GetType()) {
                    case TreeNodeBase::Type::Misc_Func: {
                        break;
                    }

                    case TreeNodeBase::Type::Definition_Typedef:
                    case TreeNodeBase::Type::Definition_Struct:
                    case TreeNodeBase::Type::Definition_Union: {
                        break;
                    }

                    case TreeNodeBase::Type::Definition_Let:
                    case TreeNodeBase::Type::Definition_Set:
                    case TreeNodeBase::Type::Definition_Const:
                    case TreeNodeBase::Type::Definition_Constexpr: {
                        break;
                    }

                    case TreeNodeBase::Type::Misc_Class: {
                        break;
                    }

                    case TreeNodeBase::Type::Misc_FromImport: {
                        break;
                    }
                }
            }
        }
    }

    const std::vector<TokenNode> Visibility::GetFunctions(const std::string& name = "") const {
        if (name == "") {
            return functions;
        }

        std::vector<TokenNode> funcs;

        return funcs;
    }

    const std::vector<TokenNode> Visibility::GetTypes(const std::string& name = "") const {
        if (name == "") {
            return types;
        }

        std::vector<TokenNode> tps;

        return tps;
    }

    const std::vector<TokenNode> Visibility::GetVariables(const std::string& name = "") const {
        if (name == "") {
            return variables;
        }

        std::vector<TokenNode> vars;

        return vars;
    }

    const std::vector<TokenNode> Visibility::GetClasses(const std::string& name = "") const {
        if (name == "") {
            return classes;
        }

        std::vector<TokenNode> cls;

        return cls;
    }

    const std::vector<TokenNode> Visibility::GetImports(const std::string& name = "") const {
        if (name == "") {
            return imports;
        }

        std::vector<TokenNode> imps;

        return imps;
    }

}