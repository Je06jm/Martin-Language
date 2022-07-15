#ifndef MARTIN_GENERATORS_CLASSTYPE
#define MARTIN_GENERATORS_CLASSTYPE

#include <parse.hpp>

namespace Martin {

    class ClassTypeVirtualTreeNode : public TreeNodeBase {
    public:
        ClassTypeVirtualTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::ClassType_Virtual;
        }

        std::string GetName() const override {
            return "Virtual";
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

            if (right->is_token) return false;

            switch (right->node->GetType()) {
                case Type::ClassType_Virtual:
                case Type::ClassType_Override:
                case Type::ClassType_Static:
                case Type::Definition_Let:
                case Type::Definition_Set:
                case Type::Definition_Const:
                case Type::Definition_Constexpr:
                case Type::Assignment_Assign:
                case Type::Assignment_TypeAssign:
                    return right->node->Valid();

                default:
                    return false;
            }
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
    };

    class ClassTypeOverrideTreeNode : public TreeNodeBase {
    public:
        ClassTypeOverrideTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::ClassType_Override;
        }

        std::string GetName() const override {
            return "Override";
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

            if (right->is_token) return false;

            switch (right->node->GetType()) {
                case Type::ClassType_Virtual:
                case Type::ClassType_Override:
                case Type::ClassType_Static:
                case Type::Definition_Let:
                case Type::Definition_Set:
                case Type::Definition_Const:
                case Type::Definition_Constexpr:
                case Type::Assignment_Assign:
                case Type::Assignment_TypeAssign:
                    return right->node->Valid();

                default:
                    return false;
            }
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
    };

    class ClassTypeStaticTreeNode : public TreeNodeBase {
    public:
        ClassTypeStaticTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::ClassType_Static;
        }

        std::string GetName() const override {
            return "Static";
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

            if (right->is_token) return false;

            switch (right->node->GetType()) {
                case Type::ClassType_Virtual:
                case Type::ClassType_Override:
                case Type::ClassType_Static:
                case Type::Definition_Let:
                case Type::Definition_Set:
                case Type::Definition_Const:
                case Type::Definition_Constexpr:
                case Type::Assignment_Assign:
                case Type::Assignment_TypeAssign:
                    return right->node->Valid();

                default:
                    return false;
            }
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
    };

    class ClassTypeTreeGenerator : public TreeNodeGenerator {
    public:
        bool IsReversed() const override {
            return true;
        }
        
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::KW_Virtual) ||
                (sym->GetType() == TokenType::Type::KW_Override) ||
                (sym->GetType() == TokenType::Type::KW_Static)
            )) {
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (right) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Virtual:
                            op = TreeNode(new ClassTypeVirtualTreeNode(right));
                            break;
                        
                        case TokenType::Type::KW_Override:
                            op = TreeNode(new ClassTypeOverrideTreeNode(right));
                            break;
                        
                        case TokenType::Type::KW_Static:
                            op = TreeNode(new ClassTypeStaticTreeNode(right));
                            break;
                    }

                    op->SetLineNumber(sym->GetLineNumber());

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 2);
                }
            }
            return 0;
        }
    };

}

#endif