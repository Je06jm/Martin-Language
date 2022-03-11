#ifndef MARTIN_GENERATORS_BITWISE
#define MARTIN_GENERATORS_BITWISE

#include <parse.hpp>

namespace Martin {

    class OPBitAndTreeNode : public TreeNodeBase {
    public:
        OPBitAndTreeNode(TokenNode left, TokenNode right) : left(left), right(right)  {}

        Type GetType() const override {
            return Type::OP_BitAnd;
        }

        std::string GetName() const override {
            return "&";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPBitOrTreeNode : public TreeNodeBase {
    public:
        OPBitOrTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_BitOr;
        }

        std::string GetName() const override {
            return "|";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPBitXOrTreeNode : public TreeNodeBase {
    public:
        OPBitXOrTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_BitXOr;
        }

        std::string GetName() const override {
            return "^";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPBitNotTreeNode : public TreeNodeBase {
    public:
        OPBitNotTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::OP_BitNot;
        }

        std::string GetName() const override {
            return "~";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
        }

    private:
        const TokenNode right;
    };

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

    class OPBitwiseTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_BitAnd) ||
                (sym->GetType() == TokenType::Type::SYM_BitOr) ||
                (sym->GetType() == TokenType::Type::SYM_BitXOr) ||
                (sym->GetType() == TokenType::Type::SYM_BitShiftLeft) ||
                (sym->GetType() == TokenType::Type::SYM_BitShiftRight)
            )) {
                TreeNode op;

                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    switch (sym->GetType()) {
                        case TokenType::Type::SYM_BitAnd:
                            op = TreeNode(new OPBitAndTreeNode(left, right));
                            break;

                        case TokenType::Type::SYM_BitOr:
                            op = TreeNode(new OPBitOrTreeNode(left, right));
                            break;

                        case TokenType::Type::SYM_BitXOr:
                            op = TreeNode(new OPBitXOrTreeNode(left, right));
                            break;

                        case TokenType::Type::SYM_BitShiftLeft:
                            op = TreeNode(new OPBitShiftLeftTreeNode(left, right));
                            break;

                        case TokenType::Type::SYM_BitShiftRight:
                            op = TreeNode(new OPBitShiftRightTreeNode(left, right));
                            break;
                    }

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                    return 3;
                }
            } else if (sym && (sym->GetType() == TokenType::Type::SYM_BitNot)) {
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (right) {
                    TreeNode op = TreeNode(new OPBitNotTreeNode(right));

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 2);

                    return 2;
                }
            }

            return 0;
        }
    };

}

#endif