#ifndef MARTIN_GENERATORS_CLASS
#define MARTIN_GENERATORS_CLASS

#include <parse.hpp>
#include "colon.hpp"
#include "comma.hpp"

namespace Martin {

    class ClassTreeNode : public TreeNodeBase {
    public:
        ClassTreeNode(TokenNode name, TokenNode scope) : name(name), scope(scope) {}

        Type GetType() const override {
            return Type::Misc_Class;
        }

        std::string GetName() const override {
            return "Class";
        }

        void Serialize(std::string& serial) const override {
            if (scope)
                serial = Format("$($, $)", GetName(), *name, *scope);
            
            else
                serial = Format("$($, nullptr)", *name, GetName());
        }

        bool Valid() const override {
            if (!name || !scope) return false;

            if (name->is_token && (name->token->GetType() != TokenType::Type::Identifier)) return false;
            else if (!name->is_token) {
                if (name->node->GetType() != Type::Misc_Colon) return false;
                if (!name->node->Valid()) return false;

                auto node = std::static_pointer_cast<ColonTreeNode>(name->node);
                
                if (!node->left->is_token) return false;
                if (node->left->token->GetType() != TokenType::Type::Identifier) return false;

                if (node->right->is_token) return false;
                if (!node->right->node->Valid()) return false;
                if (node->right->node->GetType() == Type::Struct_Comma) {
                    auto comma = std::static_pointer_cast<StructCommaTreeNode>(node->right->node);
                    for (auto it : comma->nodes) {
                        if (it->is_token) return false;
                        if (!IsAccess(it->node->GetType())) return false;
                        if (!it->node->Valid()) return false;
                    }
                } else if (!IsAccess(node->right->node->GetType())) return false;
            }

            if (scope->is_token) return false;

            if (scope->node->GetType() != Type::Struct_Curly) return false;

            return true;
        }

        const TokenNode name;
        const TokenNode scope;

        bool IsAccess(Type type) const {
            switch (type) {
                case Type::ClassAccess_Public:
                case Type::ClassAccess_Protected:
                case Type::ClassAccess_Private:
                    return true;
                
                default:
                    return false;
            }
        }
    };

    class ClassTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Class)) {
                TokenNode name = GetIndexOrNull(tree, index+1);
                TokenNode scope = GetIndexOrNull(tree, index+2);

                if (name && scope) {
                    TreeNode op = TreeNode(new ClassTreeNode(name, scope));

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 3);

                    return 3;
                }
            }
            return 0;
        }
    };

}

#endif