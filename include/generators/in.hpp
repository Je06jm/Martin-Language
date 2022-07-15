#ifndef MARTIN_GENERATORS_IN
#define MARTIN_GENERATORS_IN

#include <parse.hpp>
#include "dot.hpp"

namespace Martin {

    class InTreeNode : public TreeNodeBase {
    public:
        InTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Misc_In;
        }

        std::string GetName() const override {
            return "In";
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

            if (left->is_token) {
                if (left->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!left->node->Valid()) return false;

                switch (left->node->GetType()) {
                    case Type::Definition_Let:
                    case Type::Definition_Set:
                    case Type::Definition_Const:
                        break;
                    
                    case Type::OP_Dot: {
                            TreeNode node = left->node;
                            while (node->GetType() == Type::OP_Dot) {
                                auto dot = std::static_pointer_cast<OPDotTreeNode>(node);

                                if (!dot->left->is_token) return false;
                                if (dot->left->token->GetType() != TokenType::Type::Identifier) return false;

                                if (dot->right->is_token) {
                                    if (dot->right->token->GetType() != TokenType::Type::Identifier) return false;
                                    break;

                                } else {
                                    if (!dot->right->node->Valid()) return false;
                                    if (dot->right->node->GetType() != Type::OP_Dot) return false;
                                    node = dot->right->node;
                                    
                                }
                            }
                        break;
                    }
                    
                    default:
                        return false;
                }
            }

            if (right->is_token) {
                if (right->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!right->node->Valid()) return false;

                switch (right->node->GetType()) {
                    case Type::Definition_Let:
                    case Type::Definition_Set:
                    case Type::Definition_Const:
                        break;
                    
                    case Type::OP_Dot: {
                            TreeNode node = right->node;
                            while (node->GetType() == Type::OP_Dot) {
                                auto dot = std::static_pointer_cast<OPDotTreeNode>(node);

                                if (!dot->left->is_token) return false;
                                if (dot->left->token->GetType() != TokenType::Type::Identifier) return false;

                                if (dot->right->is_token) {
                                    if (dot->right->token->GetType() != TokenType::Type::Identifier) return false;
                                    break;

                                } else {
                                    if (!dot->right->node->Valid()) return false;
                                    if (dot->right->node->GetType() != Type::OP_Dot) return false;
                                    node = dot->right->node;
                                    
                                }
                            }
                        break;
                    }
                    
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

    class InTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);

            if (sym && (sym->GetType() == TokenType::Type::KW_In)) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op = TreeNode(new InTreeNode(left, right));

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