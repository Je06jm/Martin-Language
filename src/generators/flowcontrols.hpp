#ifndef MARTIN_GENERATORS_FLOWCONTROLS
#define MARTIN_GENERATORS_FLOWCONTROLS

#include <parse.hpp>
#include "enclosures.hpp"
#include "colon.hpp"

namespace Martin {

    class FlowControlIfTreeNode : public TreeNodeBase {
    public:
        FlowControlIfTreeNode(TokenNode condition, TokenNode scope) : condition(condition), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_If;
        }

        std::string GetName() const override {
            return "If";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        bool Valid() const override {
            if (!condition | !scope) return false;

            if (condition->is_token) {
                switch (condition->token->GetType()) {
                    case TokenType::Type::Boolean:
                    case TokenType::Type::Identifier:
                        break;
                    
                    default:
                        return false;
                }
            } else {
                if (!condition->node->Valid()) return false;
                switch (condition->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThanEquals:
                    case Type::OP_GreaterThanEquals:
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        break;
                    
                    default:
                        Print("$\n", condition->node->GetName());
                        return false;
                }
            }

            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;

            return true;
        }

        const TokenNode condition;
        const TokenNode scope;
    };

    class FlowControlElifTreeNode : public TreeNodeBase {
    public:
        FlowControlElifTreeNode(TokenNode condition, TokenNode scope) : condition(condition), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_Elif;
        }

        std::string GetName() const override {
            return "Elif";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        bool Valid() const override {
            if (!condition | !scope) return false;

            if (condition->is_token) {
                switch (condition->token->GetType()) {
                    case TokenType::Type::Boolean:
                    case TokenType::Type::Identifier:
                        break;
                    
                    default:
                        return false;
                }
            } else {
                if (!condition->node->Valid()) return false;
                switch (condition->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThanEquals:
                    case Type::OP_GreaterThanEquals:
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        break;
                    
                    default:
                        return false;
                }
            }

            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;

            return true;
        }

        const TokenNode condition;
        const TokenNode scope;
    };

    class FlowControlElseTreeNode : public TreeNodeBase {
    public:
        FlowControlElseTreeNode(TokenNode scope) : scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_Else;
        }

        std::string GetName() const override {
            return "Else";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *scope);
        }

        bool Valid() const override {
            if (!scope) return false;
            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;

            return true;
        }

        const TokenNode scope;
    };

    class FlowControlWhileTreeNode : public TreeNodeBase {
    public:
        FlowControlWhileTreeNode(TokenNode condition, TokenNode scope) : condition(condition), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_While;
        }

        std::string GetName() const override {
            return "While";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        bool Valid() const override {
            if (!condition | !scope) return false;

            if (condition->is_token) {
                switch (condition->token->GetType()) {
                    case TokenType::Type::Boolean:
                    case TokenType::Type::Identifier:
                        break;
                    
                    default:
                        return false;
                }
            } else {
                if (!condition->node->Valid()) return false;
                switch (condition->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThanEquals:
                    case Type::OP_GreaterThanEquals:
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        break;
                    
                    default:
                        return false;
                }
            }

            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;

            return true;
        }

        const TokenNode condition;
        const TokenNode scope;
    };

    class FlowControlForTreeNode : public TreeNodeBase {
    public:
        FlowControlForTreeNode(TokenNode start, TokenNode condition, TokenNode increment, TokenNode scope) : start(start), condition(condition), increment(increment), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_For;
        }

        std::string GetName() const override {
            return "For";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        bool Valid() const override {
            if (start) {
                if (start->is_token) return false;
                if (!start->node->Valid()) return false;
                switch (start->node->GetType()) {
                    case Type::Assignment_Assign:
                    case Type::Assignment_TypeAssign:
                        break;
                    
                    default:
                        return false;
                }
            }

            if (!condition) return false;
            if (condition->is_token) {
                switch (condition->token->GetType()) {
                    case TokenType::Type::Boolean:
                    case TokenType::Type::Identifier:
                        break;
                    
                    default:
                        return false;
                }
            } else {
                if (!condition->node->Valid()) return false;
                switch (condition->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                    case Type::OP_Equals:
                    case Type::OP_NotEquals:
                    case Type::OP_LessThan:
                    case Type::OP_GreaterThan:
                    case Type::OP_LessThanEquals:
                    case Type::OP_GreaterThanEquals:
                    case Type::OP_LogicalAnd:
                    case Type::OP_LogicalOr:
                    case Type::OP_LogicalNot:
                        break;

                    default:
                        return false;
                }
            }

            if (!scope) return false;
            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;

            return true;
        }
        
        const TokenNode start;
        const TokenNode condition;
        const TokenNode increment;
        const TokenNode scope;
    };

    class FlowControlForeachTreeNode : public TreeNodeBase {
    public:
        FlowControlForeachTreeNode(TokenNode condition, TokenNode scope) : condition(condition), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_Foreach;
        }

        std::string GetName() const override {
            return "Foreach";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        bool Valid() const override {
            if (!condition || !scope) return false;

            if (condition->is_token) return false;
            if (!condition->node->Valid()) return false;
            if (condition->node->GetType() != Type::Misc_In) return false;

            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;
            
            return true;
        }

        const TokenNode condition;
        const TokenNode scope;
    };

    class FlowControlSwitchTreeNode : public TreeNodeBase {
    public:
        FlowControlSwitchTreeNode(TokenNode condition, TokenNode scope) : condition(condition), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_Switch;
        }

        std::string GetName() const override {
            return "Switch";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        bool Valid() const override {
            if (!condition || !scope) return false;

            if (condition->is_token) {
                if (condition->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!condition->node->Valid()) return false;
                switch (condition->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                        break;
                    
                    default:
                        return false;
                }
            }

            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;
            
            auto curly = std::static_pointer_cast<StructCurlyTreeNode>(scope->node);
            auto tree = curly->inside;

            for (auto it : (*tree)) {
                if (it->is_token) return false;
                if (it->node->GetType() != Type::Misc_Colon) return false;
                auto colon = std::static_pointer_cast<ColonTreeNode>(it->node);

                if (!colon->left->is_token) return false;
                if (colon->left->token->GetType() != TokenType::Type::Identifier) return false;
            }

            return true;
        }

        const TokenNode condition;
        const TokenNode scope;
    };

    class FlowControlMatchTreeNode : public TreeNodeBase {
    public:
        FlowControlMatchTreeNode(TokenNode condition, TokenNode scope) : condition(condition), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_Match;
        }

        std::string GetName() const override {
            return "Match";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        bool Valid() const override {
            if (!condition || !scope) return false;

            if (condition->is_token) {
                if (condition->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!condition->node->Valid()) return false;
                switch (condition->node->GetType()) {
                    case Type::OP_Dot:
                    case Type::Misc_Call:
                        break;
                    
                    default:
                        return false;
                }
            }

            if (scope->is_token) return false;
            if (!scope->node->Valid()) return false;
            if (scope->node->GetType() != Type::Struct_Curly) return false;
            
            auto curly = std::static_pointer_cast<StructCurlyTreeNode>(scope->node);
            auto tree = curly->inside;

            for (auto it : (*tree)) {
                if (it->is_token) return false;
                if (it->node->GetType() != Type::Misc_Colon) return false;
                auto colon = std::static_pointer_cast<ColonTreeNode>(it->node);

                if (!colon->left->is_token) return false;
            }

            return true;
        }

        const TokenNode condition;
        const TokenNode scope;
    };

    class FlowControlContinueTreeNode : public TreeNodeBase {
    public:
        FlowControlContinueTreeNode() {}

        Type GetType() const override {
            return Type::FlowControl_Continue;
        }

        std::string GetName() const override {
            return "Continue";
        }

        void Serialize(std::string& serial) const override {
            serial = GetName();
        }
    };

    class FlowControlBreakTreeNode : public TreeNodeBase {
    public:
        FlowControlBreakTreeNode() {}

        Type GetType() const override {
            return Type::FlowControl_Break;
        }

        std::string GetName() const override {
            return "Break";
        }

        void Serialize(std::string& serial) const override {
            serial = GetName();
        }
    };

    class FlowControlReturnTreeNode : public TreeNodeBase {
    public:
        FlowControlReturnTreeNode(TokenNode returns) : returns(returns) {}

        Type GetType() const override {
            return Type::FlowControl_Return;
        }

        std::string GetName() const override {
            return "Return";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *returns);
        }

        bool Valid() const override {
            if (!returns) return false;

            return ValidateTokenNode(returns);
        }

        const TokenNode returns;

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
                    case Type::Struct_Parentheses:
                        return node->node->Valid();
                    
                    default:
                        return false;
                }
            }
        }
    };

    class FlowControlsTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::KW_If) ||
                (sym->GetType() == TokenType::Type::KW_Elif) ||
                (sym->GetType() == TokenType::Type::KW_While) ||
                (sym->GetType() == TokenType::Type::KW_For) ||
                (sym->GetType() == TokenType::Type::KW_Foreach) ||
                (sym->GetType() == TokenType::Type::KW_Switch) ||
                (sym->GetType() == TokenType::Type::KW_Match)
            )) {
                TokenNode condition = GetIndexOrNull(tree, index+1);
                TokenNode scope = GetIndexOrNull(tree, index+2);

                if (condition && scope) {
                    Tree cond_tree;
                    if (condition->is_token) return 0;
                    if (!condition->node->Valid()) return 0;
                    if (condition->node->GetType() != TreeNodeBase::Type::Struct_Parentheses) return 0;
                    auto pare = std::static_pointer_cast<StructParenthesesTreeNode>(condition->node);
                    cond_tree = pare->inside;
                    if (cond_tree->size() != 1) return 0;
                    
                    TreeNode op;
                    

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_If:
                            op = TreeNode(new FlowControlIfTreeNode((*cond_tree)[0], scope));
                            break;
                        
                        case TokenType::Type::KW_Elif:
                            op = TreeNode(new FlowControlElifTreeNode((*cond_tree)[0], scope));
                            break;
                        
                        case TokenType::Type::KW_While:
                            op = TreeNode(new FlowControlWhileTreeNode((*cond_tree)[0], scope));
                            break;

                        case TokenType::Type::KW_For: {
                                TokenNode start, cond, incr;
                                
                                if ((*cond_tree)[0]->node->GetType() != TreeNodeBase::Type::Struct_Comma) return 0;
                                auto comma = std::static_pointer_cast<StructCommaTreeNode>((*cond_tree)[0]->node);

                                if (comma->nodes.size() == 2) {
                                    start = nullptr;
                                    cond = comma->nodes[0];
                                    incr = comma->nodes[1];
                                } else if (comma->nodes.size() == 3) {
                                    start = comma->nodes[0];
                                    cond = comma->nodes[1];
                                    incr = comma->nodes[2];
                                } else {
                                    return 0;
                                }

                                op = TreeNode(new FlowControlForTreeNode(start, cond, incr, scope));
                                break;
                            }
                        
                        case TokenType::Type::KW_Foreach:
                            op = TreeNode(new FlowControlForeachTreeNode((*cond_tree)[0], scope));
                            break;
                        
                        case TokenType::Type::KW_Switch:
                            op = TreeNode(new FlowControlSwitchTreeNode((*cond_tree)[0], scope));
                            break;
                        
                        case TokenType::Type::KW_Match:
                            op = TreeNode(new FlowControlMatchTreeNode((*cond_tree)[0], scope));
                            break;
                    }

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 3);

                    return 3;
                }
            } else if (sym && (
                (sym->GetType() == TokenType::Type::KW_Else) ||
                (sym->GetType() == TokenType::Type::KW_Return)
            )) {
                TokenNode right = GetIndexOrNull(tree, index+1);
                
                if (right) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Else:
                            op = TreeNode(new FlowControlElseTreeNode(right));
                            break;
                        
                        case TokenType::Type::KW_Return:
                            op = TreeNode(new FlowControlReturnTreeNode(right));
                            break;
                    }

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 2);

                    return 2;
                }
            } else if (sym && (
                (sym->GetType() == TokenType::Type::KW_Continue) ||
                (sym->GetType() == TokenType::Type::KW_Break)
            )) {
                TreeNode op;

                switch (sym->GetType()) {
                    case TokenType::Type::KW_Continue:
                        op = TreeNode(new FlowControlContinueTreeNode);
                        break;
                    
                    case TokenType::Type::KW_Break:
                        op = TreeNode(new FlowControlBreakTreeNode);
                        break;
                }

                TokenNode token_node = TokenNode(new TokenNodeBase);
                token_node->node = op;
                ReplaceTreeWithTokenNode(tree, token_node, index, 1);

                return 1;
            }
            return 0;
        }
    };

}

#endif