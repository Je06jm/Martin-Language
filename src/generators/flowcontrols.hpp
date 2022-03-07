#include <parse.hpp>

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

        const TokenNode condition;
        const TokenNode scope;
    };

    class FlowControlForTreeNode : public TreeNodeBase {
    public:
        FlowControlForTreeNode(TokenNode condition, TokenNode scope) : condition(condition), scope(scope) {}

        Type GetType() const override {
            return Type::FlowControl_For;
        }

        std::string GetName() const override {
            return "For";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *condition, *scope);
        }

        const TokenNode condition;
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
            return "Match";
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

        const TokenNode returns;
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
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_If:
                            op = TreeNode(new FlowControlIfTreeNode(condition, scope));
                            break;
                        
                        case TokenType::Type::KW_Elif:
                            op = TreeNode(new FlowControlElifTreeNode(condition, scope));
                            break;
                        
                        case TokenType::Type::KW_While:
                            op = TreeNode(new FlowControlWhileTreeNode(condition, scope));
                            break;

                        case TokenType::Type::KW_For:
                            op = TreeNode(new FlowControlForTreeNode(condition, scope));
                            break;
                        
                        case TokenType::Type::KW_Foreach:
                            op = TreeNode(new FlowControlForeachTreeNode(condition, scope));
                            break;
                        
                        case TokenType::Type::KW_Switch:
                            op = TreeNode(new FlowControlSwitchTreeNode(condition, scope));
                            break;
                        
                        case TokenType::Type::KW_Match:
                            op = TreeNode(new FlowControlMatchTreeNode(condition, scope));
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