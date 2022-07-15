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
                    case Type::Struct_Parentheses:
                        return true;
                    
                    default:
                        return false;
                }
            }
        }
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
                    case Type::Struct_Parentheses:
                        return true;
                    
                    default:
                        return false;
                }
            }
        }
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
                    case Type::Struct_Parentheses:
                        return true;
                    
                    default:
                        return false;
                }
            }
        }
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

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!right) return false;
            
            if (!ValidateTokenNode(right)) return false;

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;
            
            if (!right->is_token) {
                if (right->node->GetType() == type) {
                    list.push_back(right->node);
                }
                auto list2 = right->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

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
                    case Type::Struct_Parentheses:
                        return true;
                    
                    default:
                        return false;
                }
            }
        }
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
                    case Type::Struct_Parentheses:
                        return true;
                    
                    default:
                        return false;
                }
            }
        }
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
                    case Type::Struct_Parentheses:
                        return true;
                    
                    default:
                        return false;
                }
            }
        }
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

                    op->SetLineNumber(sym->GetLineNumber());

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                    return 3;
                }
            } else if (sym && (sym->GetType() == TokenType::Type::SYM_BitNot)) {
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (right) {
                    TreeNode op = TreeNode(new OPBitNotTreeNode(right));

                    op->SetLineNumber(sym->GetLineNumber());

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