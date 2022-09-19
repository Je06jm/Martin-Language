#ifndef MARTIN_GENERATORS_ARROW
#define MARTIN_GENERATORS_ARROW

#include <parse.hpp>
#include "enclosures.hpp"
#include "comma.hpp"
#include "rettypes.hpp"

namespace Martin {

    class ArrowTreeNode : public TreeNodeBase {
    public:
        ArrowTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Misc_Arrow;
        }

        std::string GetName() const override {
            return "->";
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

            if (left->is_token) return false;
            if (right->is_token) {
                if (right->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                switch (right->node->GetType()) {
                    case Type::ReturnType_Let:
                    case Type::ReturnType_Set:
                    case Type::ReturnType_Const:
                    case Type::ReturnType_Constexpr:
                        break;
                    
                    case Type::Struct_Curly: {
                        auto curly = std::static_pointer_cast<StructCurlyTreeNode>(right->node);
                        auto tree = curly->inside;

                        if (tree->size() == 0) return false;
                        
                        if ((*tree)[0]->is_token) {
                            if ((*tree)[0]->token->GetType() != TokenType::Type::Identifier) return false;
                            for (auto it : *(tree)) {
                                if (!it->is_token) return false;
                                if (it->token->GetType() != TokenType::Type::Identifier) return false;
                            }
                        } else {
                            switch ((*tree)[0]->node->GetType()) {
                                case Type::ReturnType_Let:
                                case Type::ReturnType_Set:
                                case Type::ReturnType_Const:
                                case Type::ReturnType_Constexpr:
                                    break;

                                case Type::Struct_Comma: {
                                    auto comma = std::static_pointer_cast<StructCommaTreeNode>((*tree)[0]->node);
                                    for (auto it : comma->nodes) {
                                        if (it->is_token) {
                                            if (it->token->GetType() != TokenType::Type::Identifier) return false;
                                        } else {
                                            switch (it->node->GetType()) {
                                                case Type::ReturnType_Let:
                                                case Type::ReturnType_Set:
                                                case Type::ReturnType_Const:
                                                case Type::ReturnType_Constexpr:
                                                    break;
                                                
                                                default:
                                                    return false;
                                            }
                                        }
                                    }
                                    break;
                                }

                                default:
                                    return false;
                            }
                        }
                        break;
                    }

                    default:
                        return false;
                }
            }

            switch (left->node->GetType()) {
                case Type::Struct_Parentheses:
                case Type::Definition_Typedef:
                case Type::Misc_Call:
                    break;
                
                default:
                    return false;
            }

            return left->node->Valid();
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

    class ArrowTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::SYM_Arrow)) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op = TreeNode(new ArrowTreeNode(left, right));

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