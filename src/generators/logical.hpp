#include <parse.hpp>

namespace Martin {

    class OPLogicalAndTreeNode : public TreeNodeBase {
    public:
        OPLogicalAndTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_LogicalAnd;
        }

        std::string GetName() const override {
            return "and";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPLogicalOrTreeNode : public TreeNodeBase {
    public:
        OPLogicalOrTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_LogicalOr;
        }

        std::string GetName() const override {
            return "or";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPLogicalNotTreeNode : public TreeNodeBase {
    public:
        OPLogicalNotTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::OP_LogicalNot;
        }

        std::string GetName() const override {
            return "not";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
        }

    private:
        const TokenNode right;
    };

    class OPLogicalsTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::KW_And) ||
                (sym->GetType() == TokenType::Type::KW_Or) ||
                (sym->GetType() == TokenType::Type::KW_Not)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (right && (sym->GetType() == TokenType::Type::KW_Not)) {
                    TreeNode op = TreeNode(new OPLogicalNotTreeNode(right));

                    if (right->is_token && !TypeHelper::CanDoLogic(right))
                        Fatal("Invalid right hand side for $ operator on line $\n", op->GetName(), right->token->GetLineNumber());
                    
                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 2);

                    return 2;
                } else if (left && right) {
                    TreeNode op;

                    if (sym->GetType() == TokenType::Type::KW_And)
                        op = TreeNode(new OPLogicalAndTreeNode(left, right));
                    
                    else
                        op = TreeNode(new OPLogicalOrTreeNode(left, right));
                    
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