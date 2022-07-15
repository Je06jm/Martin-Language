#ifndef MARTIN_GENERATORS_EQUALITY
#define MARTIN_GENERATORS_EQUALITY

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

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!left->is_token) {
                if (left->node->GetType() == type) {
                    list.push_back(left->node);
                }
                auto list2 = left->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            
            if (!right->is_token) {
                if (right->node->GetType() == type) {
                    list.push_back(right->node);
                }
                auto list2 = right->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

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
                    case TokenType::Type::Boolean:
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
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        return node->node->Valid();

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

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!left->is_token) {
                if (left->node->GetType() == type) {
                    list.push_back(left->node);
                }
                auto list2 = left->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            
            if (!right->is_token) {
                if (right->node->GetType() == type) {
                    list.push_back(right->node);
                }
                auto list2 = right->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

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
                    case TokenType::Type::Boolean:
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
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        return node->node->Valid();

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

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!left->is_token) {
                if (left->node->GetType() == type) {
                    list.push_back(left->node);
                }
                auto list2 = left->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            
            if (!right->is_token) {
                if (right->node->GetType() == type) {
                    list.push_back(right->node);
                }
                auto list2 = right->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

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
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        return node->node->Valid();

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

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!left->is_token) {
                if (left->node->GetType() == type) {
                    list.push_back(left->node);
                }
                auto list2 = left->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            
            if (!right->is_token) {
                if (right->node->GetType() == type) {
                    list.push_back(right->node);
                }
                auto list2 = right->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

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
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        return node->node->Valid();

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

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!left->is_token) {
                if (left->node->GetType() == type) {
                    list.push_back(left->node);
                }
                auto list2 = left->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            
            if (!right->is_token) {
                if (right->node->GetType() == type) {
                    list.push_back(right->node);
                }
                auto list2 = right->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

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
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        return node->node->Valid();

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

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!left || !right) return false;

            if (!ValidateTokenNode(left)) return false;
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!left->is_token) {
                if (left->node->GetType() == type) {
                    list.push_back(left->node);
                }
                auto list2 = left->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }
            
            if (!right->is_token) {
                if (right->node->GetType() == type) {
                    list.push_back(right->node);
                }
                auto list2 = right->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

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
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        return node->node->Valid();

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

                    op->SetLineNumber(sym->GetLineNumber());

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