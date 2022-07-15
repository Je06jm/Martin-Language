#ifndef MARTIN_GENERATORS_CALL
#define MARTIN_GENERATORS_CALL

#include <parse.hpp>

namespace Martin {

    class CallTreeNode : public TreeNodeBase {
    public:
        CallTreeNode(TokenNode id, TokenNode right) : id(id), right(right) {}

        Type GetType() const override {
            return Type::Misc_Call;
        }

        std::string GetName() const override {
            return "Call";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *id, *right);
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!id || !right) return false;

            if (id->is_token) {
                if (id->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (id->node->GetType() != TreeNodeBase::Type::OP_Dot) return false;
                if (!id->node->Valid()) return false;
            }

            if (right->is_token) return false;

            if (right->node->GetType() != Type::Struct_Parentheses) return false;

            return right->node->Valid();
        }
        
        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;
            
            if (!id->is_token) {
                if (id->node->GetType() == type) {
                    list.push_back(id->node);
                }
                auto list2 = id->node->GetAllNodesOfType(type);
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

        const TokenNode id;
        const TokenNode right;
    };

    class CallTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            TokenNode sym = GetIndexOrNull(tree, index);
            if (sym && (
                (sym->is_token && (sym->token->GetType() == TokenType::Type::Identifier)) ||
                (!sym->is_token && (sym->node->GetType() == TreeNodeBase::Type::OP_Dot))
            )) {
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (right && !right->is_token && (right->node->GetType() == TreeNodeBase::Type::Struct_Parentheses)) {
                    TreeNode op = TreeNode(new CallTreeNode(sym, right));

                    if (sym->is_token) {
                        op->SetLineNumber(sym->token->GetLineNumber());
                    } else {
                        op->SetLineNumber(sym->node->GetLineNumber());
                    }

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