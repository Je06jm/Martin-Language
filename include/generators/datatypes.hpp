#ifndef MARTIN_GENERATORS_DATATYPE
#define MARTIN_GENERATORS_DATATYPE

#include <parse.hpp>
#include "enclosures.hpp"
#include "assignments.hpp"

namespace Martin {

    class StructTreeNode : public TreeNodeBase {
    public:
        StructTreeNode(TokenNode name, TokenNode members) : name(name), members(members)  {}

        Type GetType() const override {
            return Type::Definition_Struct;
        }

        std::string GetName() const override {
            return "Struct";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *name, *members);
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!name || !members) return false;

            if (!name->is_token) return false;
            if (name->token->GetType() != TokenType::Type::Identifier) return false;

            if (members->is_token) return false;
            if (!members->node->Valid()) return false;
            if (members->node->GetType() != Type::Struct_Curly) return false;

            auto curly = std::static_pointer_cast<StructCurlyTreeNode>(members->node);
            for (auto it : *(curly->inside)) {
                if (it->is_token) return false;
                if (!it->node->Valid()) return false;

                switch(it->node->GetType()) {
                    case Type::Definition_Let:
                    case Type::Definition_Set:
                    case Type::Definition_Const:
                    case Type::Definition_Constexpr:
                        break;
                    
                    default:
                        return false;
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!name->is_token) {
                if (name->node->GetType() == type) {
                    list.push_back(name->node);
                }
                auto list2 = name->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            if (!members->is_token) {
                if (members->node->GetType() == type) {
                    list.push_back(members->node);
                }
                auto list2 = members->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

        const TokenNode name;
        const TokenNode members;    
    };

    class UnionTreeNode : public TreeNodeBase {
    public:
        UnionTreeNode(TokenNode name, TokenNode members) : name(name), members(members)  {}

        Type GetType() const override {
            return Type::Definition_Union;
        }

        std::string GetName() const override {
            return "Union";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *name, *members);
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!name || !members) return false;

            if (!name->is_token) return false;
            if (name->token->GetType() != TokenType::Type::Identifier) return false;

            if (members->is_token) return false;
            if (!members->node->Valid()) return false;
            if (members->node->GetType() != Type::Struct_Curly) return false;

            auto curly = std::static_pointer_cast<StructCurlyTreeNode>(members->node);
            for (auto it : *(curly->inside)) {
                if (it->is_token) return false;
                if (!it->node->Valid()) return false;

                switch(it->node->GetType()) {
                    case Type::Definition_Let:
                    case Type::Definition_Set:
                    case Type::Definition_Const:
                    case Type::Definition_Constexpr:
                        break;
                    
                    default:
                        return false;
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!name->is_token) {
                if (name->node->GetType() == type) {
                    list.push_back(name->node);
                }
                auto list2 = name->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            if (!members->is_token) {
                if (members->node->GetType() == type) {
                    list.push_back(members->node);
                }
                auto list2 = members->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

        const TokenNode name;
        const TokenNode members;    
    };

    class EnumTreeNode : public TreeNodeBase {
    public:
        EnumTreeNode(TokenNode name, TokenNode members) : name(name), members(members)  {}

        Type GetType() const override {
            return Type::Definition_Enum;
        }

        std::string GetName() const override {
            return "Enum";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *name, *members);
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!name || !members) return false;

            if (!name->is_token) return false;
            if (name->token->GetType() != TokenType::Type::Identifier) return false;

            if (members->is_token) return false;
            if (!members->node->Valid()) return false;
            if (members->node->GetType() != Type::Struct_Curly) return false;

            auto curly = std::static_pointer_cast<StructCurlyTreeNode>(members->node);
            for (auto it : *(curly->inside)) {
                if (it->is_token) {
                    if (it->token->GetType() != TokenType::Type::Identifier) return false;
                } else {
                    if (!it->node->Valid()) return false;
                    if (it->node->GetType() != Type::Assignment_Assign) return false;

                    auto assign = std::static_pointer_cast<AssignTreeNode>(it->node);

                    if (!assign->left->is_token) return false;
                    if (assign->left->token->GetType() != TokenType::Type::Identifier) return false;

                    if (!assign->right->is_token) return false;
                    switch (assign->right->token->GetType()) {
                        case TokenType::Type::Integer:
                        case TokenType::Type::UInteger:
                            break;
                        default:
                            return false;
                    }
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            if (!name->is_token) {
                if (name->node->GetType() == type) {
                    list.push_back(name->node);
                }
                auto list2 = name->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            if (!members->is_token) {
                if (members->node->GetType() == type) {
                    list.push_back(members->node);
                }
                auto list2 = members->node->GetAllNodesOfType(type);
                list.insert(list.end(), list2.begin(), list2.end());
            }

            return list;
        }

        const TokenNode name;
        const TokenNode members;    
    };

    class DataTypesTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::KW_Struct) ||
                (sym->GetType() == TokenType::Type::KW_Union) ||
                (sym->GetType() == TokenType::Type::KW_Enum)
            )) {
                TokenNode id = GetIndexOrNull(tree, index+1);
                TokenNode members = GetIndexOrNull(tree, index+2);

                if (id && members) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Struct:
                            op = TreeNode(new StructTreeNode(id, members));
                            break;
                        
                        case TokenType::Type::KW_Union:
                            op = TreeNode(new UnionTreeNode(id, members));
                            break;
                        
                        case TokenType::Type::KW_Enum:
                            op = TreeNode(new EnumTreeNode(id, members));
                            break;
                    }

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