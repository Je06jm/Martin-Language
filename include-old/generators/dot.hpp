#ifndef MARTIN_GENERATORS_DOT
#define MARTIN_GENERATORS_DOT

#include <parse.hpp>

namespace Martin {

    class OPDotTreeNode : public TreeNodeBase {
    public:
        OPDotTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Dot;
        }

        std::string GetName() const override {
            return ".";
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

            if (!left->is_token) return false;
            if (left->token->GetType() != TokenType::Type::Identifier) return false;
            if (right->is_token) {
                if (right->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                switch (right->node->GetType()) {
                    case Type::OP_Dot:
                        if (!right->node->Valid()) return false;
                        break;
                    
                    default:
                        return false;
                }
            }

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
    };

    class OPDotTreeGenerator : public TreeNodeGenerator {
    public:
        bool IsReversed() const override {
            return true;
        }

        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::SYM_Period)) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op = TreeNode(new OPDotTreeNode(left, right));

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