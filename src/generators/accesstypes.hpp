#ifndef MARTIN_GENERATOR_ACCESSTYPES
#define MARTIN_GENERATOR_ACCESSTYPES

#include <parse.hpp>
#include "comma.hpp"
#include "enclosures.hpp"

namespace Martin {

    class ArrayTypesTreeNode : public TreeNodeBase {
    public:
        ArrayTypesTreeNode(const std::vector<Token>& sizes, TokenNode right) : sizes(sizes), right(right) {}

        Type GetType() const override {
            return Type::Access_Array;
        }

        std::string GetName() const override {
            return "Array";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
        }
        
        bool Valid() const override {
            if (sizes.size() == 0) return 0;
            for (auto it : sizes) {
                switch (it->GetType()) {
                    case TokenType::Type::Integer:
                    case TokenType::Type::UInteger:
                        break;
                    
                    default:
                        return false;
                }
            }

            if (right) {
                if (right->is_token && (right->token->GetType() != TokenType::Type::Identifier))
                    return false;
                
                else if (!right->is_token) {
                    switch (right->node->GetType()) {
                        case Type::Access_Pointer:
                        case Type::Access_Reference:
                        case Type::Access_Shared:
                        case Type::Access_Unique:
                        case Type::Access_Array:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            return right != nullptr;
        }
        

        const std::vector<Token> sizes;
        const TokenNode right;
    };

    class ReferenceTypesTreeNode : public TreeNodeBase {
    public:
        ReferenceTypesTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::Access_Reference;
        }

        std::string GetName() const override {
            return "Reference";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
            
        }

        bool Valid() const override {
            if (right) {
                if (right->is_token && (right->token->GetType() != TokenType::Type::Identifier))
                    return false;
                
                else if (!right->is_token) {
                    switch (right->node->GetType()) {
                        case TreeNodeBase::Type::Access_Array:
                        case TreeNodeBase::Type::Access_Pointer:
                        case TreeNodeBase::Type::Access_Reference:
                        case TreeNodeBase::Type::Access_Shared:
                        case TreeNodeBase::Type::Access_Unique:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            return right != nullptr;
        }

        const TokenNode right;
    };

    class SharedTypesTreeNode : public TreeNodeBase {
    public:
        SharedTypesTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::Access_Shared;
        }

        std::string GetName() const override {
            return "Shared";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
            
        }

        bool Valid() const override {
            if (right) {
                if (right->is_token && (right->token->GetType() != TokenType::Type::Identifier))
                    return false;
                
                else if (!right->is_token) {
                    switch (right->node->GetType()) {
                        case TreeNodeBase::Type::Access_Array:
                        case TreeNodeBase::Type::Access_Pointer:
                        case TreeNodeBase::Type::Access_Reference:
                        case TreeNodeBase::Type::Access_Shared:
                        case TreeNodeBase::Type::Access_Unique:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            return right != nullptr;
        }

        const TokenNode right;
    };

    class UniqueTypesTreeNode : public TreeNodeBase {
    public:
        UniqueTypesTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::Access_Unique;
        }

        std::string GetName() const override {
            return "Unique";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
            
        }

        bool Valid() const override {
            if (right) {
                if (right->is_token && (right->token->GetType() != TokenType::Type::Identifier))
                    return false;
                
                else if (!right->is_token) {
                    switch (right->node->GetType()) {
                        case TreeNodeBase::Type::Access_Array:
                        case TreeNodeBase::Type::Access_Pointer:
                        case TreeNodeBase::Type::Access_Reference:
                        case TreeNodeBase::Type::Access_Shared:
                        case TreeNodeBase::Type::Access_Unique:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            return right != nullptr;
        }

        const TokenNode right;
    };

    class PointerTypesTreeNode : public TreeNodeBase {
    public:
        PointerTypesTreeNode(TokenNode right) : right(right) {}

        Type GetType() const override {
            return Type::Access_Pointer;
        }

        std::string GetName() const override {
            return "Pointer";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), *right);
            
        }

        bool Valid() const override {
            if (right) {
                if (right->is_token && (right->token->GetType() != TokenType::Type::Identifier))
                    return false;
                
                else if (!right->is_token) {
                    switch (right->node->GetType()) {
                        case TreeNodeBase::Type::Access_Array:
                        case TreeNodeBase::Type::Access_Pointer:
                        case TreeNodeBase::Type::Access_Reference:
                        case TreeNodeBase::Type::Access_Shared:
                        case TreeNodeBase::Type::Access_Unique:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            return right != nullptr;
        }

        const TokenNode right;
    };

    class AccessTypesTreeGenerator : public TreeNodeGenerator {
    public:
        bool IsReversed() const override {
            return true;
        }

        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Array)) {
                TokenNode sizes = GetIndexOrNull(tree, index+1);
                TokenNode right = GetIndexOrNull(tree, index+2);

                if (sizes && right) {
                    std::vector<Token> vsizes;
                    
                    if (sizes->is_token) {
                        switch (sizes->token->GetType()) {
                            case TokenType::Type::Integer:
                            case TokenType::Type::UInteger:
                                vsizes.push_back(sizes->token);
                                break;
                            
                            default:
                                return 0;
                        }
                    } else {
                        if (!sizes->node->Valid()) return 0;
                        if (sizes->node->GetType() != TreeNodeBase::Type::Struct_Bracket) return false;
                        auto bracket = std::static_pointer_cast<StructBracketTreeNode>(sizes->node);
                        auto inside = bracket->inside;
                        if (inside->size() != 0) {
                            if ((*inside)[0]->is_token) {
                                switch((*inside)[0]->token->GetType()) {
                                    case TokenType::Type::Integer:
                                    case TokenType::Type::UInteger:
                                        vsizes.push_back((*inside)[0]->token);
                                        break;
                                    
                                    default:
                                        return 0;
                                }
                            } else {
                                if (!(*inside)[0]->node->Valid()) return 0;
                                if ((*inside)[0]->node->GetType() != TreeNodeBase::Type::Struct_Comma) return 0;
                                
                                auto comma = std::static_pointer_cast<StructCommaTreeNode>((*inside)[0]->node);
                                for (auto it : comma->nodes) {
                                    if (!it->is_token) return 0;
                                    switch (it->token->GetType()) {
                                        case TokenType::Type::Integer:
                                        case TokenType::Type::UInteger:
                                            vsizes.push_back(it->token);
                                            break;
                                        
                                        default:
                                            return 0;
                                    }
                                }
                            }
                        }
                    }
                    TreeNode op = TreeNode(new ArrayTypesTreeNode(vsizes, right));

                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index, 3);

                    return 3;
                }
            } else if (sym && (
                (sym->GetType() == TokenType::Type::KW_Reference) ||
                (sym->GetType() == TokenType::Type::KW_Shared) ||
                (sym->GetType() == TokenType::Type::KW_Unique) ||
                (sym->GetType() == TokenType::Type::KW_Pointer)
            )) {
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (right) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Reference:
                            op = TreeNode(new ReferenceTypesTreeNode(right));
                            break;
                        
                        case TokenType::Type::KW_Pointer:
                            op = TreeNode(new PointerTypesTreeNode(right));
                            break;
                        
                        case TokenType::Type::KW_Unique:
                            op = TreeNode(new UniqueTypesTreeNode(right));
                            break;
                        
                        case TokenType::Type::KW_Shared:
                            op = TreeNode(new SharedTypesTreeNode(right));
                            break;
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