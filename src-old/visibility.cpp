#include <visibility.hpp>

#include "generators/funclambda.hpp"
#include "generators/datatypes.hpp"
#include "generators/assignments.hpp"
#include "generators/class.hpp"
#include "generators/fromimport.hpp"
#include "generators/arrow.hpp"

namespace Martin {

    bool HasSubMatch(const TokenNode id, const std::string& match, size_t offset=0) {
        std::string string;

        Token id_token = id->token;

        auto id_ptr = std::static_pointer_cast<uint8_t[]>(id_token->GetData());
        string = *(id_ptr.get());

        for (size_t i = 0; i < match.size(); i++) {
            if ((i + offset) >= string.size()) {
                return false;
            }

            if (string[i + offset] != match[i]) {
                return false;
            }
        }

        return true;
    }

    Visibility::Visibility(Tree tree) {
        for (auto token_node : (*tree)) {
            if (!token_node->is_token) {
                switch (token_node->node->GetType()) {
                    case TreeNodeBase::Type::Misc_Func: {
                        auto node = std::static_pointer_cast<FuncTreeNode>(token_node->node);
                        auto arrow = std::static_pointer_cast<ArrowTreeNode>(node->arrow->node);
                        TokenNode id = arrow->right;

                        functions.push_back({ id });
                        break;
                    }

                    case TreeNodeBase::Type::Definition_Typedef: {
                        auto node = std::static_pointer_cast<TypedefTreeNode>(token_node->node);
                        
                        for (auto id : node->ids) {
                            TokenNode new_token_node = TokenNode(new TokenNodeBase);
                            new_token_node->is_token = true;
                            new_token_node->token = id;
                            types.push_back({ new_token_node });
                        }
                        break;
                    }

                    case TreeNodeBase::Type::Definition_Enum:
                    case TreeNodeBase::Type::Definition_Struct:
                    case TreeNodeBase::Type::Definition_Union: {
                        auto node = std::static_pointer_cast<StructTreeNode>(token_node->node);
                        types.push_back({ node->name });
                        break;
                    }

                    case TreeNodeBase::Type::Definition_Let:
                    case TreeNodeBase::Type::Definition_Set:
                    case TreeNodeBase::Type::Definition_Const:
                    case TreeNodeBase::Type::Definition_Constexpr: {
                        auto node = std::static_pointer_cast<LetTreeNode>(token_node->node);

                        for (auto id : node->ids) {
                            auto new_token_node = TokenNode(new TokenNodeBase);
                            new_token_node->is_token = true;
                            new_token_node->token = id;

                            variables.push_back({ new_token_node });
                        }
                        break;
                    }

                    case TreeNodeBase::Type::Misc_Class: {
                        auto node = std::static_pointer_cast<ClassTreeNode>(token_node->node);

                        if (node->name->is_token) {
                            classes.push_back({ node->name });
                        } else {
                            auto colon = std::static_pointer_cast<ColonTreeNode>(node->name->node);

                            classes.push_back({ colon->left });
                        }
                        break;
                    }

                    case TreeNodeBase::Type::Misc_FromImport: {
                        auto node = std::static_pointer_cast<MiscFromImportTreeNode>(token_node->node);
                        for (auto id : node->ids) {
                            imports.push_back({ id });
                        }
                        break;
                    }
                }
            }
        }
    }

    const std::vector<Visibility::VisibilityNode> Visibility::GetFunctions(const std::string& name) const {
        if (name == "") {
            return functions;
        }

        std::vector<VisibilityNode> funcs;

        for (auto node : functions) {
            if (HasSubMatch(node.id, name, 0)) {
                funcs.push_back(node);
            }
        }

        return funcs;
    }

    const std::vector<Visibility::VisibilityNode> Visibility::GetTypes(const std::string& name) const {
        if (name == "") {
            return types;
        }

        std::vector<VisibilityNode> tps;

        for (auto node : types) {
            if (HasSubMatch(node.id, name, 0)) {
                tps.push_back(node);
            }
        }

        return tps;
    }

    const std::vector<Visibility::VisibilityNode> Visibility::GetVariables(const std::string& name) const {
        if (name == "") {
            return variables;
        }

        std::vector<VisibilityNode> vars;

        for (auto node : variables) {
            if (HasSubMatch(node.id, name, 0)) {
                vars.push_back(node);
            }
        }

        return vars;
    }

    const std::vector<Visibility::VisibilityNode> Visibility::GetClasses(const std::string& name) const {
        if (name == "") {
            return classes;
        }

        std::vector<VisibilityNode> cls;

        for (auto node : classes) {
            if (HasSubMatch(node.id, name, 0)) {
                cls.push_back(node);
            }
        }

        return cls;
    }

    const std::vector<Visibility::VisibilityNode> Visibility::GetImports(const std::string& name) const {
        if (name == "") {
            return imports;
        }

        std::vector<VisibilityNode> imps;

        for (auto node : imports) {
            if (HasSubMatch(node.id, name, 0)) {
                imps.push_back(node);
            }
        }

        return imps;
    }

}