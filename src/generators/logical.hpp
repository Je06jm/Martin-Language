#ifndef MARTIN_GENERATORS_LOGICAL
#define MARTIN_GENERATORS_LOGICAL

#include <parse.hpp>
#include "enclosures.hpp"

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

        bool Valid() const override {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        static bool ValidateTokenNode(TokenNode node) {
            if (node->is_token) {
                switch (node->token->GetType()) {
                    case TokenType::Type::Identifier:
                    case TokenType::Type::Boolean:
                        break;
                    
                    default:
                        return false;
                }
            } else {
                if (!node->node->Valid()) return false;
                switch (node->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThanEquals:
                    case Type::OP_GreaterThanEquals:
                        break;

                    case Type::Struct_Parentheses: {
                        auto parenth = std::static_pointer_cast<StructParenthesesTreeNode>(node->node);
                        auto tree = parenth->inside;

                        if (tree->size() != 1) return false;

                        if (!ValidateTokenNode((*tree)[0])) return false;

                        break;
                    }
                    
                    default:
                        return false;
                }
            }
            
            return true;
        }

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

        bool Valid() const override {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        static bool ValidateTokenNode(TokenNode node) {
            if (node->is_token) {
                switch (node->token->GetType()) {
                    case TokenType::Type::Identifier:
                    case TokenType::Type::Boolean:
                        break;
                    
                    default:
                        return false;
                }
            } else {
                if (!node->node->Valid()) return false;
                switch (node->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThanEquals:
                    case Type::OP_GreaterThanEquals:
                        break;

                    case Type::Struct_Parentheses: {
                        auto parenth = std::static_pointer_cast<StructParenthesesTreeNode>(node->node);
                        auto tree = parenth->inside;

                        if (tree->size() != 1) return false;

                        if (!ValidateTokenNode((*tree)[0])) return false;

                        break;
                    }
                    
                    default:
                        return false;
                }
            }
            
            return true;
        }

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

        bool Valid() const override {
            if (!right) return false;

            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        static bool ValidateTokenNode(TokenNode node) {
            if (node->is_token) {
                switch (node->token->GetType()) {
                    case TokenType::Type::Identifier:
                    case TokenType::Type::Boolean:
                        break;
                    
                    default:
                        return false;
                }
            } else {
                if (!node->node->Valid()) return false;
                switch (node->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThanEquals:
                    case Type::OP_GreaterThanEquals:
                        break;

                    case Type::Struct_Parentheses: {
                        auto parenth = std::static_pointer_cast<StructParenthesesTreeNode>(node->node);
                        auto tree = parenth->inside;

                        if (tree->size() != 1) return false;

                        if (!ValidateTokenNode((*tree)[0])) return false;

                        break;
                    }
                    
                    default:
                        return false;
                }
            }
            
            return true;
        }

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

                if (left && right) {
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

    class OPNotLogicTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym &&  (sym->GetType() == TokenType::Type::KW_Not)) {
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (right) {
                    TreeNode op = TreeNode(new OPLogicalNotTreeNode(right));
                    
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