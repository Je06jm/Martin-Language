#ifndef MARTIN_GENERATORS_EXTERN
#define MARTIN_GENERATORS_EXTERN

#include <parse.hpp>
#include "assignments.hpp"

namespace Martin {

    class ExternTreeNode : public TreeNodeBase {
    public:
        ExternTreeNode(Token type, TokenNode right) : type(type), right(right) {}

        Type GetType() const override {
            return Type::Misc_Extern;
        }

        std::string GetName() const override {
            return "Extern";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), type->GetName(), *right);
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!type || !right) return false;

            if (type->GetType() != TokenType::Type::String8) return false;

            if (right->is_token) return false;
            if (!right->node->Valid()) return false;

            switch (right->node->GetType()) {
                case Type::Definition_Let:
                case Type::Definition_Set:
                case Type::Definition_Const:
                case Type::Definition_Constexpr:
                case Type::Misc_Func:
                case Type::Misc_Class:
                    break;
                
                case Type::Assignment_Assign: {
                    auto assign = std::static_pointer_cast<AssignTreeNode>(right->node);
                    if (assign->left->is_token) return false;
                    
                    switch (assign->left->node->GetType()) {
                        case Type::Definition_Let:
                        case Type::Definition_Set:
                        case Type::Definition_Const:
                        case Type::Definition_Constexpr:
                            break;
                        
                        default:
                            return false;
                    }
                }

                default:
                    return false;
            }

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

        const Token type;
        const TokenNode right;
    };

    class ExternTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Extern)) {
                Token type = GetIndexOrNullToken(tree, index+1);
                TokenNode right = GetIndexOrNull(tree, index+2);

                if (type && right) {
                    TreeNode op = TreeNode(new ExternTreeNode(type, right));

                    op->SetLineNumber(sym->GetLineNumber());

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 3);

                    return 3;
                }
            }
            return 0;
        }
    };

}

#endif