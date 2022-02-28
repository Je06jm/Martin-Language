#include <parse.hpp>

namespace Martin {

    class OPEqualsTreeNode : public TreeNodeBase {
    public:
        OPEqualsTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Equals;
        }

        std::string GetName() const override {
            return "==";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPNotEqualsTreeNode : public TreeNodeBase {
    public:
        OPNotEqualsTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_NotEquals;
        }

        std::string GetName() const override {
            return "!=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPLessThanTreeNode : public TreeNodeBase {
    public:
        OPLessThanTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_LessThan;
        }

        std::string GetName() const override {
            return "<";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPGreaterThanTreeNode : public TreeNodeBase {
    public:
        OPGreaterThanTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_GreaterThan;
        }

        std::string GetName() const override {
            return ">";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPLessThanEqualsTreeNode : public TreeNodeBase {
    public:
        OPLessThanEqualsTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_LessThanEquals;
        }

        std::string GetName() const override {
            return "<=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPGreaterThanEqualsTreeNode : public TreeNodeBase {
    public:
        OPGreaterThanEqualsTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_GreaterThanEquals;
        }

        std::string GetName() const override {
            return ">=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPEqualityTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_Equals) ||
                (sym->GetType() == TokenType::Type::SYM_NotEquals) ||
                (sym->GetType() == TokenType::Type::SYM_LessThan) ||
                (sym->GetType() == TokenType::Type::SYM_GreaterThan) ||
                (sym->GetType() == TokenType::Type::SYM_LessThanEquals) ||
                (sym->GetType() == TokenType::Type::SYM_GreaterThanEquals)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::SYM_Equals:
                            op = TreeNode(new OPEqualsTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_NotEquals:
                            op = TreeNode(new OPNotEqualsTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_LessThan:
                            op = TreeNode(new OPLessThanTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_GreaterThan:
                            op = TreeNode(new OPGreaterThanTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_LessThanEquals:
                            op = TreeNode(new OPLessThanEqualsTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_GreaterThanEquals:
                            op = TreeNode(new OPGreaterThanEqualsTreeNode(left, right));
                            break;
                    }

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