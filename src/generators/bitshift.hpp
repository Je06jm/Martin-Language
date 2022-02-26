#include <parse.hpp>

#include <logging.hpp>

#include "typehelper.hpp"

namespace Martin {

    class OPBitShiftLeftTreeNode : public TreeNodeBase {
    public:
        OPBitShiftLeftTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_BitShiftLeft;
        }

        std::string GetName() const override {
            return "<<";
        }

    private:
            const TokenNode left;
            const TokenNode right;
    };

    class OPBitShiftRightTreeNode : public TreeNodeBase {
    public:
        OPBitShiftRightTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_BitShiftRight;
        }

        std::string GetName() const override {
            return ">>";
        }

    private:
            const TokenNode left;
            const TokenNode right;
    };

    class OPBitShiftTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_BitShiftLeft) ||
                (sym->GetType() == TokenType::Type::SYM_BitShiftRight)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op;

                    if (sym->GetType() == TokenType::Type::SYM_BitShiftLeft)
                        op = TreeNode(new OPBitShiftLeftTreeNode(left, right));
                    
                    else
                        op = TreeNode(new OPBitShiftRightTreeNode(left, right));
                    
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