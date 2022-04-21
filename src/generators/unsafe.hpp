#ifndef MARTIN_GENERATORS_UNSAFE
#define MARTIN_GENERATORS_UNSAFE

#include <parse.hpp>
#include "assignments.hpp"

namespace Martin {

    class UnsafeTreeNode : public TreeNodeBase {
    public:
        UnsafeTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::Misc_Unsafe;
        }

        std::string GetName() const override {
            return "Unsafe";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
        }

        bool Valid() const override {
            if (!right) return false;

            if (right->is_token) return false;
            if (!right->node->Valid()) return false;

            switch (right->node->GetType()) {
                case Type::Definition_Let:
                case Type::Definition_Set:
                case Type::Definition_Const:
                case Type::Definition_Constexpr:
                case Type::Misc_Func:
                case Type::Struct_Curly:
                case Type::Assignment_TypeAssign:
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

                    break;
                }

                default:
                    return false;
            }

            return true;
        }

        const TokenNode right;
    };

    class UnsafeTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Unsafe)) {
                TokenNode right = GetIndexOrNull(tree, index+1);
                
                if (right) {
                    TreeNode op = TreeNode(new UnsafeTreeNode(right));

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