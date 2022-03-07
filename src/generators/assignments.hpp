#include <parse.hpp>

namespace Martin {

    class AssignTreeNode : public TreeNodeBase {
    public:
        AssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_Assign;
        }

        std::string GetName() const override {
            return "=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class TypeAssignTreeNode : public TreeNodeBase {
    public:
        TypeAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_Assign;
        }

        std::string GetName() const override {
            return ":=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class AddAssignTreeNode : public TreeNodeBase {
    public:
        AddAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_AddAssign;
        }

        std::string GetName() const override {
            return "+=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class SubAssignTreeNode : public TreeNodeBase {
    public:
        SubAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_SubAssign;
        }

        std::string GetName() const override {
            return "-=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class MulAssignTreeNode : public TreeNodeBase {
    public:
        MulAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_MulAssign;
        }

        std::string GetName() const override {
            return "*=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class DivAssignTreeNode : public TreeNodeBase {
    public:
        DivAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_DivAssign;
        }

        std::string GetName() const override {
            return "/=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class ModAssignTreeNode : public TreeNodeBase {
    public:
        ModAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_ModAssign;
        }

        std::string GetName() const override {
            return "%=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class PowAssignTreeNode : public TreeNodeBase {
    public:
        PowAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_Assign;
        }

        std::string GetName() const override {
            return "**=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class BitAndAssignTreeNode : public TreeNodeBase {
    public:
        BitAndAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_BitAndAssign;
        }

        std::string GetName() const override {
            return "&=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class BitOrAssignTreeNode : public TreeNodeBase {
    public:
        BitOrAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_BitOrAssign;
        }

        std::string GetName() const override {
            return "|=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class BitXOrAssignTreeNode : public TreeNodeBase {
    public:
        BitXOrAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_BitXOrAssign;
        }

        std::string GetName() const override {
            return "^=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };
    
    class BitNotAssignTreeNode : public TreeNodeBase {
    public:
        BitNotAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_BitNotAssign;
        }

        std::string GetName() const override {
            return "~=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class BitShiftLeftAssignTreeNode : public TreeNodeBase {
    public:
        BitShiftLeftAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_BitShiftLeftAssign;
        }

        std::string GetName() const override {
            return "<<=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class BitShiftRightAssignTreeNode : public TreeNodeBase {
    public:
        BitShiftRightAssignTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Assignment_BitShiftRightAssign;
        }

        std::string GetName() const override {
            return ">>=";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class AssignmentsTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_Assign) ||
                (sym->GetType() == TokenType::Type::SYM_TypeAssign) ||
                (sym->GetType() == TokenType::Type::SYM_AssignAdd) ||
                (sym->GetType() == TokenType::Type::SYM_AssignSub) ||
                (sym->GetType() == TokenType::Type::SYM_AssignMul) ||
                (sym->GetType() == TokenType::Type::SYM_AssignDiv) ||
                (sym->GetType() == TokenType::Type::SYM_AssignMod) ||
                (sym->GetType() == TokenType::Type::SYM_AssignPow) ||
                (sym->GetType() == TokenType::Type::SYM_AssignBitAnd) ||
                (sym->GetType() == TokenType::Type::SYM_AssignBitOr) ||
                (sym->GetType() == TokenType::Type::SYM_AssignBitXOr) ||
                (sym->GetType() == TokenType::Type::SYM_AssignBitNot) ||
                (sym->GetType() == TokenType::Type::SYM_AssignBitShiftLeft) ||
                (sym->GetType() == TokenType::Type::SYM_AssignBitShiftRight)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::SYM_Assign:
                            op = TreeNode(new AssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_TypeAssign:
                            op = TreeNode(new TypeAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignAdd:
                            op = TreeNode(new AddAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignSub:
                            op = TreeNode(new SubAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignMul:
                            op = TreeNode(new MulAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignDiv:
                            op = TreeNode(new DivAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignMod:
                            op = TreeNode(new ModAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignPow:
                            op = TreeNode(new PowAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignBitAnd:
                            op = TreeNode(new BitAndAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignBitOr:
                            op = TreeNode(new BitOrAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignBitXOr:
                            op = TreeNode(new BitXOrAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignBitShiftLeft:
                            op = TreeNode(new BitShiftLeftAssignTreeNode(left, right));
                            break;
                        
                        case TokenType::Type::SYM_AssignBitShiftRight:
                            op = TreeNode(new BitShiftRightAssignTreeNode(left, right));
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