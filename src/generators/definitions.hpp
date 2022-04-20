#ifndef MARTIN_GENERATORS_DEFINITIONS
#define MARTIN_GENERATORS_DEFINITIONS

#include <parse.hpp>
#include "enclosures.hpp"
#include "comma.hpp"

namespace Martin {

    class LetTreeNode : public TreeNodeBase {
    public:
        LetTreeNode(std::vector<Token> ids, TokenNode types) : ids(ids), types(types) {}

        Type GetType() const override {
            return Type::Definition_Let;
        }

        std::string GetName() const override {
            return "Let";
        }

        void Serialize(std::string& serial) const override {
            std::string name = GetName();
            serial = Format("$((", name);
            
            for (size_t i = 0; i < ids.size(); i++) {
                if (ids[i]) {
                    name = ids[i]->GetName();
                    serial = serial + name;

                    if (i < (ids.size() - 1))
                        serial = Format("$, ", serial);
                    else
                        serial = Format("$)", serial);
                } else
                    break;
            }

            if (types)
                serial = Format("$, $)", serial, *types);
            else
                serial = Format("$, nullptr)", serial);
        }

        bool Valid() const override {
            if (ids.size() == 0) return false;
            if (!types) return false;

            if (types->is_token) {
                if (types->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!types->node->Valid()) return false;
                switch (types->node->GetType()) {
                    case Type::Misc_Arrow:
                    case Type::Access_Pointer:
                    case Type::Access_Reference:
                    case Type::Access_Shared:
                    case Type::Access_Unique:
                    case Type::Access_Array:
                        break;

                    case Type::Struct_Curly: {
                        auto curly = std::static_pointer_cast<StructCurlyTreeNode>(types->node);
                        auto tree = curly->inside;
                        if (tree->size() == 0) return false;

                        if ((*tree)[0]->is_token) {
                            if ((*tree)[0]->token->GetType() != TokenType::Type::Identifier) return false;
                        } else {
                            if ((*tree)[0]->node->GetType() != Type::Struct_Comma) return false;
                            auto comma = std::static_pointer_cast<StructCommaTreeNode>((*tree)[0]->node);
                            if (!comma->Valid()) return false;

                            for (auto it : comma->nodes) {
                                if (!it->is_token) return false;
                                if (it->token->GetType() != TokenType::Type::Identifier) return false;
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

        const std::vector<Token> ids;
        const TokenNode types;  
    };

    class SetTreeNode : public TreeNodeBase {
    public:
        SetTreeNode(std::vector<Token> ids, TokenNode types) : ids(ids), types(types) {}

        Type GetType() const override {
            return Type::Definition_Set;
        }

        std::string GetName() const override {
            return "Set";
        }

        void Serialize(std::string& serial) const override {
            std::string name = GetName();
            serial = Format("$((", name);
            
            for (size_t i = 0; i < ids.size(); i++) {
                if (ids[i]) {
                    name = ids[i]->GetName();
                    serial = serial + name;

                    if (i < (ids.size() - 1))
                        serial = Format("$, ", serial);
                    else
                        serial = Format("$)", serial);
                } else
                    break;
            }

            if (types)
                serial = Format("$, $)", serial, *types);
            else
                serial = Format("$, nullptr)", serial);
        }

        bool Valid() const override {
            if (ids.size() == 0) return false;
            if (!types) return false;

            if (types->is_token) {
                if (types->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!types->node->Valid()) return false;
                switch (types->node->GetType()) {
                    case Type::Misc_Arrow:
                    case Type::Access_Pointer:
                    case Type::Access_Reference:
                    case Type::Access_Shared:
                    case Type::Access_Unique:
                    case Type::Access_Array:
                        break;

                    case Type::Struct_Curly: {
                        auto curly = std::static_pointer_cast<StructCurlyTreeNode>(types->node);
                        auto tree = curly->inside;
                        if (tree->size() == 0) return false;

                        if ((*tree)[0]->is_token) {
                            if ((*tree)[0]->token->GetType() != TokenType::Type::Identifier) return false;
                        } else {
                            if ((*tree)[0]->node->GetType() != Type::Struct_Comma) return false;
                            auto comma = std::static_pointer_cast<StructCommaTreeNode>((*tree)[0]->node);
                            if (!comma->Valid()) return false;

                            for (auto it : comma->nodes) {
                                if (!it->is_token) return false;
                                if (it->token->GetType() != TokenType::Type::Identifier) return false;
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

        const std::vector<Token> ids;
        const TokenNode types;   
    };

    class ConstTreeNode : public TreeNodeBase {
    public:
        ConstTreeNode(std::vector<Token> ids, TokenNode types) : ids(ids), types(types) {}

        Type GetType() const override {
            return Type::Definition_Const;
        }

        std::string GetName() const override {
            return "Const";
        }

        void Serialize(std::string& serial) const override {
            std::string name = GetName();
            serial = Format("$((", name);
            
            for (size_t i = 0; i < ids.size(); i++) {
                if (ids[i]) {
                    name = ids[i]->GetName();
                    serial = serial + name;

                    if (i < (ids.size() - 1))
                        serial = Format("$, ", serial);
                    else
                        serial = Format("$)", serial);
                } else
                    break;
            }

            if (types)
                serial = Format("$, $)", serial, *types);
            else
                serial = Format("$, nullptr)", serial);
        }

        bool Valid() const override {
            if (ids.size() == 0) return false;
            if (!types) return false;

            if (types->is_token) {
                if (types->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!types->node->Valid()) return false;
                switch (types->node->GetType()) {
                    case Type::Misc_Arrow:
                    case Type::Access_Pointer:
                    case Type::Access_Reference:
                    case Type::Access_Shared:
                    case Type::Access_Unique:
                    case Type::Access_Array:
                        break;

                    case Type::Struct_Curly: {
                        auto curly = std::static_pointer_cast<StructCurlyTreeNode>(types->node);
                        auto tree = curly->inside;
                        if (tree->size() == 0) return false;

                        if ((*tree)[0]->is_token) {
                            if ((*tree)[0]->token->GetType() != TokenType::Type::Identifier) return false;
                        } else {
                            if ((*tree)[0]->node->GetType() != Type::Struct_Comma) return false;
                            auto comma = std::static_pointer_cast<StructCommaTreeNode>((*tree)[0]->node);
                            if (!comma->Valid()) return false;

                            for (auto it : comma->nodes) {
                                if (!it->is_token) return false;
                                if (it->token->GetType() != TokenType::Type::Identifier) return false;
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

        const std::vector<Token> ids;
        const TokenNode types;   
    };

    class ConstexprTreeNode : public TreeNodeBase {
    public:
        ConstexprTreeNode(std::vector<Token> ids, TokenNode types) : ids(ids), types(types) {}

        Type GetType() const override {
            return Type::Definition_Constexpr;
        }

        std::string GetName() const override {
            return "Constexpr";
        }

        void Serialize(std::string& serial) const override {
            std::string name = GetName();
            serial = Format("$((", name);
            
            for (size_t i = 0; i < ids.size(); i++) {
                if (ids[i]) {
                    name = ids[i]->GetName();
                    serial = serial + name;

                    if (i < (ids.size() - 1))
                        serial = Format("$, ", serial);
                    else
                        serial = Format("$)", serial);
                } else
                    break;
            }

            if (types)
                serial = Format("$, $)", serial, *types);
            else
                serial = Format("$, nullptr)", serial);
        }

        bool Valid() const override {
            if (ids.size() == 0) return false;
            if (!types) return false;

            if (types->is_token) {
                if (types->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                if (!types->node->Valid()) return false;
                switch (types->node->GetType()) {
                    case Type::Misc_Arrow:
                    case Type::Access_Pointer:
                    case Type::Access_Reference:
                    case Type::Access_Shared:
                    case Type::Access_Unique:
                    case Type::Access_Array:
                        break;

                    case Type::Struct_Curly: {
                        auto curly = std::static_pointer_cast<StructCurlyTreeNode>(types->node);
                        auto tree = curly->inside;
                        if (tree->size() == 0) return false;

                        if ((*tree)[0]->is_token) {
                            if ((*tree)[0]->token->GetType() != TokenType::Type::Identifier) return false;
                        } else {
                            if ((*tree)[0]->node->GetType() != Type::Struct_Comma) return false;
                            auto comma = std::static_pointer_cast<StructCommaTreeNode>((*tree)[0]->node);
                            if (!comma->Valid()) return false;

                            for (auto it : comma->nodes) {
                                if (!it->is_token) return false;
                                if (it->token->GetType() != TokenType::Type::Identifier) return false;
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

        const std::vector<Token> ids;
        const TokenNode types;
    };

    class TypedefTreeNode : public TreeNodeBase {
    public:
        TypedefTreeNode(std::vector<Token> ids, TokenNode types) : ids(ids), types(types) {}

        Type GetType() const override {
            return Type::Definition_Typedef;
        }

        std::string GetName() const override {
            return "Typedef";
        }

        void Serialize(std::string& serial) const override {
            std::string name = GetName();
            serial = Format("$((", name);
            
            for (size_t i = 0; i < ids.size(); i++) {
                if (ids[i]) {
                    name = ids[i]->GetName();
                    serial = serial + name;

                    if (i < (ids.size() - 1))
                        serial = Format("$, ", serial);
                    else
                        serial = Format("$)", serial);
                } else
                    break;
            }

            if (types)
                serial = Format("$, $)", serial, *types);
            else
                serial = Format("$, nullptr)", serial);
        }

        const std::vector<Token> ids;
        const TokenNode types;
    };

    class DefinitionsTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::KW_Let) ||
                (sym->GetType() == TokenType::Type::KW_Set) ||
                (sym->GetType() == TokenType::Type::KW_Const) ||
                (sym->GetType() == TokenType::Type::KW_Constexpr) ||
                (sym->GetType() == TokenType::Type::KW_Typedef)
            )) {
                TokenNode id = GetIndexOrNull(tree, index+1);
                std::vector<Token> ids;
                size_t i = index+1;
                for (; i < end; i += 2) {
                    Token id = GetIndexOrNullToken(tree, i);
                    if (!id)
                        break;
                    
                    ids.push_back(id);

                    Token comma = GetIndexOrNullToken(tree, i+1);
                    if (!comma || (comma->GetType() != TokenType::Type::SYM_Comma))
                        break;
                }

                Token colon = GetIndexOrNullToken(tree, i+1);
                TokenNode types = GetIndexOrNull(tree, i+2);

                if (colon && types && (colon->GetType() == TokenType::Type::SYM_Colon)) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Let:
                            op = TreeNode(new LetTreeNode(ids, types));
                            break;
                        
                        case TokenType::Type::KW_Set:
                            op = TreeNode(new SetTreeNode(ids, types));
                            break;
                        
                        case TokenType::Type::KW_Const:
                            op = TreeNode(new ConstTreeNode(ids, types));
                            break;
                        
                        case TokenType::Type::KW_Constexpr:
                            op = TreeNode(new ConstexprTreeNode(ids, types));
                            break;

                        case TokenType::Type::KW_Typedef:
                            op = TreeNode(new TypedefTreeNode(ids, types));
                            break;
                    }

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, i+3 - index);

                    return i+3 - index;
                } else if (colon && types && (colon->GetType() == TokenType::Type::SYM_TypeAssign)) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Let:
                            op = TreeNode(new LetTreeNode(ids, nullptr));
                            break;
                        
                        case TokenType::Type::KW_Set:
                            op = TreeNode(new SetTreeNode(ids, nullptr));
                            break;
                        
                        case TokenType::Type::KW_Const:
                            op = TreeNode(new ConstTreeNode(ids, nullptr));
                            break;
                        
                        case TokenType::Type::KW_Constexpr:
                            op = TreeNode(new ConstexprTreeNode(ids, nullptr));
                            break;

                        case TokenType::Type::KW_Typedef:
                            op = TreeNode(new TypedefTreeNode(ids, nullptr));
                            break;
                    }

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, i+1 - index);

                    return i+1 - index;
                }
            }
            return 0;
        }
    };

}

#endif