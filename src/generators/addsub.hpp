#ifndef MARTIN_GENERATOR_ADDSUB
#define MARTIN_GENERATOR_ADDSUB

#include <parse.hpp>

#include <logging.hpp>
#include "enclosures.hpp"

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

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        bool Valid() const override {
            if (!left || !right) return false;
            
            if (left->is_token && right->is_token) {
                TokenType::Type left_type = left->token->GetType();
                TokenType::Type right_type = right->token->GetType();

                if (
                    (
                        (left_type == TokenType::Type::String8) ||
                        (left_type == TokenType::Type::String16) ||
                        (left_type == TokenType::Type::String32) ||
                        (left_type == TokenType::Type::String16l) ||
                        (left_type == TokenType::Type::String32l) ||
                        (left_type == TokenType::Type::String16b) ||
                        (left_type == TokenType::Type::String32b)
                    ) &&
                    (
                        (right_type == TokenType::Type::String8) ||
                        (right_type == TokenType::Type::String16) ||
                        (right_type == TokenType::Type::String32) ||
                        (right_type == TokenType::Type::String16l) ||
                        (right_type == TokenType::Type::String32l) ||
                        (right_type == TokenType::Type::String16b) ||
                        (right_type == TokenType::Type::String32b)
                    )
                ) return true;
            }

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }
    
    private:
        const TokenNode left;
        const TokenNode right;

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

    class OPSubTreeNode : public TreeNodeBase {
    public:
        OPSubTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Sub;
        }

        std::string GetName() const override {
            return "-";
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

    private:
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
                        
                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                    return 3;
                }
            } else if (sym && (sym->GetType() == TokenType::Type::Integer)) {
                // Do something here? The tokenizer probably converted 1-2 into
                // Integer 1, Integer -2
            }

            return 0;
        }
    };

}

#endif