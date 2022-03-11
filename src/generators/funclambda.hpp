#ifndef MARTIN_GENERATORS_FUNCLAMBDA
#define MARTIN_GENERATORS_FUNCLAMBDA

#include <parse.hpp>

namespace Martin {

    class FuncTreeNode : public TreeNodeBase {
    public:
        FuncTreeNode(TokenNode arrow, TokenNode scope) : arrow(arrow), scope(scope) {}

        Type GetType() const override {
            return Type::Misc_Func;
        }

        std::string GetName() const override {
            return "Func";
        }

        void Serialize(std::string& serial) const override {
            if (scope)
                serial = Format("$($, $)", GetName(), *arrow, *scope);
            else
                serial = Format("$($, nullptr)", GetName(), *arrow);
        }

        const TokenNode arrow;
        const TokenNode scope;
    };

    class LambdaTreeNode : public TreeNodeBase {
    public:
        LambdaTreeNode(TokenNode arrow, TokenNode scope) : arrow(arrow), scope(scope) {}

        Type GetType() const override {
            return Type::Misc_Lambda;
        }

        std::string GetName() const override {
            return "Lambda";
        }

        void Serialize(std::string& serial) const override {
            if (scope)
                serial = Format("$($, $)", GetName(), *arrow, *scope);
            else
                serial = Format("$($, nullptr)", GetName(), *arrow);
        }

        const TokenNode arrow;
        const TokenNode scope;
    };

    class FuncLambdaTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Func)) {
                TokenNode arrow = GetIndexOrNull(tree, index+1);
                TokenNode scope = GetIndexOrNull(tree, index+2);

                if (arrow && scope && (!scope->is_token) && (scope->node->GetType() == TreeNodeBase::Type::Struct_Curly)) {
                    TreeNode op = TreeNode(new FuncTreeNode(arrow, scope));

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 3);

                    return 3;
                } else if (arrow) {
                    TreeNode op = TreeNode(new FuncTreeNode(arrow, nullptr));

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 2);

                    return 2;
                }
            } else if (sym && (sym->GetType() == TokenType::Type::KW_Lambda)) {
                TokenNode arrow = GetIndexOrNull(tree, index+1);
                TokenNode scope = GetIndexOrNull(tree, index+2);

                if (arrow && scope) {
                    TreeNode op = TreeNode(new LambdaTreeNode(arrow, scope));

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