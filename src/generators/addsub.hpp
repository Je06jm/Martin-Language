#include <parse.hpp>

#include <logging.hpp>

#include "typehelper.hpp"

namespace Martin {

    class OPAddTreeNode : public TreeNodeBase {
    public:
        OPAddTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Add;
        }

        std::string GetName() const override {
            return "+";
        }
    
    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPSubTreeNode : public TreeNodeBase {
    public:
        OPSubTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Sub;
        }

        std::string GetName() const override {
            return "-";
        }

    private:
            TokenNode left;
            TokenNode right;
    };

    class OPAddSubTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_Add) ||
                (sym->GetType() == TokenType::Type::SYM_Sub)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op;

                    if (sym->GetType() == TokenType::Type::SYM_Add)
                        op = TreeNode(new OPAddTreeNode(left, right));
                    
                    else
                        op = TreeNode(new OPSubTreeNode(left, right));

                    if (left->is_token && !TypeHelper::CanDoMath(left))
                        Fatal("Invalid left hand side for $ operator on line $\n", op->GetName(), left->token->GetLineNumber());
                    
                    else if (right->is_token && !TypeHelper::CanDoMath(right))
                        Fatal("Invalid right hand side for $ operator on line $\n", op->GetName(), right->token->GetLineNumber());

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                    return 3;
                }
            }

            return 0;
        }
    };

}