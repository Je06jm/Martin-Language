#ifndef MARTIN_GENERATORS_MULDIVMOD
#define MARTIN_GENERATORS_MULDIVMOD

#include <parse.hpp>

namespace Martin {

    class OPMulTreeNode : public TreeNodeBase {
    public:
        OPMulTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Mul;
        }

        std::string GetName() const override {
            return "*";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        bool Valid() const override {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        TokenNode left;
        TokenNode right;

        static bool ValidateTokenNode(TokenNode node) {
            if (node->is_token) {
                switch (node->token->GetType()) {
                    case TokenType::Type::UInteger:
                    case TokenType::Type::Integer:
                    case TokenType::Type::FloatingSingle:
                    case TokenType::Type::FloatingDouble:
                    case TokenType::Type::Identifier:
                        return true;
                    
                    default:
                        return false;
                }
            } else {
                switch (node->node->GetType()) {
                    case Type::OP_Add:
                    case Type::OP_Sub:
                    case Type::OP_Mul:
                    case Type::OP_Div:
                    case Type::OP_Mod:
                    case Type::OP_Pow:
                    case Type::OP_BitAnd:
                    case Type::OP_BitOr:
                    case Type::OP_BitXOr:
                    case Type::OP_BitNot:
                    case Type::OP_BitShiftLeft:
                    case Type::OP_BitShiftRight:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThanEquals:
                    case Type::OP_LessThanEquals:
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                        return true;

                    case Type::Struct_Parentheses: {
                        auto parenth = std::static_pointer_cast<StructParenthesesTreeNode>(node->node);
                        auto tree = parenth->inside;
                        if (tree->size() != 1) return false;
                        TokenNode token_node = (*tree)[0];
                        return ValidateTokenNode(token_node);
                    }
                    
                    default:
                        return false;
                }
            }
        }
    };

    class OPDivTreeNode : public TreeNodeBase {
    public:
        OPDivTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Div;
        }

        std::string GetName() const override {
            return "/";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        bool Valid() const override {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        TokenNode left;
        TokenNode right;

        static bool ValidateTokenNode(TokenNode node) {
            if (node->is_token) {
                switch (node->token->GetType()) {
                    case TokenType::Type::UInteger:
                    case TokenType::Type::Integer:
                    case TokenType::Type::FloatingSingle:
                    case TokenType::Type::FloatingDouble:
                    case TokenType::Type::Identifier:
                        return true;
                    
                    default:
                        return false;
                }
            } else {
                switch (node->node->GetType()) {
                    case Type::OP_Add:
                    case Type::OP_Sub:
                    case Type::OP_Mul:
                    case Type::OP_Div:
                    case Type::OP_Mod:
                    case Type::OP_Pow:
                    case Type::OP_BitAnd:
                    case Type::OP_BitOr:
                    case Type::OP_BitXOr:
                    case Type::OP_BitNot:
                    case Type::OP_BitShiftLeft:
                    case Type::OP_BitShiftRight:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThanEquals:
                    case Type::OP_LessThanEquals:
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                        return true;

                    case Type::Struct_Parentheses: {
                        auto parenth = std::static_pointer_cast<StructParenthesesTreeNode>(node->node);
                        auto tree = parenth->inside;
                        if (tree->size() != 1) return false;
                        TokenNode token_node = (*tree)[0];
                        return ValidateTokenNode(token_node);
                    }
                    
                    default:
                        return false;
                }
            }
        }
    };

    class OPModTreeNode : public TreeNodeBase {
    public:
        OPModTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Mod;
        }

        std::string GetName() const override {
            return "%";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        bool Valid() const override {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        TokenNode left;
        TokenNode right;

        static bool ValidateTokenNode(TokenNode node) {
            if (node->is_token) {
                switch (node->token->GetType()) {
                    case TokenType::Type::UInteger:
                    case TokenType::Type::Integer:
                    case TokenType::Type::FloatingSingle:
                    case TokenType::Type::FloatingDouble:
                    case TokenType::Type::Identifier:
                        return true;
                    
                    default:
                        return false;
                }
            } else {
                switch (node->node->GetType()) {
                    case Type::OP_Add:
                    case Type::OP_Sub:
                    case Type::OP_Mul:
                    case Type::OP_Div:
                    case Type::OP_Mod:
                    case Type::OP_Pow:
                    case Type::OP_BitAnd:
                    case Type::OP_BitOr:
                    case Type::OP_BitXOr:
                    case Type::OP_BitNot:
                    case Type::OP_BitShiftLeft:
                    case Type::OP_BitShiftRight:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThanEquals:
                    case Type::OP_LessThanEquals:
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                        return true;

                    case Type::Struct_Parentheses: {
                        auto parenth = std::static_pointer_cast<StructParenthesesTreeNode>(node->node);
                        auto tree = parenth->inside;
                        if (tree->size() != 1) return false;
                        TokenNode token_node = (*tree)[0];
                        return ValidateTokenNode(token_node);
                    }
                    
                    default:
                        return false;
                }
            }
        }
    };

    class OPMulDivModTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_Mul) ||
                (sym->GetType() == TokenType::Type::SYM_Div) ||
                (sym->GetType() == TokenType::Type::SYM_Mod)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op;
                    
                    if (sym->GetType() == TokenType::Type::SYM_Mul)
                        op = TreeNode(new OPMulTreeNode(left, right));
                    
                    else if (sym->GetType() == TokenType::Type::SYM_Div)
                        op = TreeNode(new OPDivTreeNode(left, right));
                    
                    else
                        op = TreeNode(new OPModTreeNode(left, right));
                    
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

#endif