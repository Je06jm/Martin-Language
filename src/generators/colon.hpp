#ifndef MARTIN_GENERATORS_COLON
#define MARTIN_GENERATORS_COLON

#include <parse.hpp>
#include "enclosures.hpp"
#include "comma.hpp"

namespace Martin {

    class ColonTreeNode : public TreeNodeBase {
    public:
        ColonTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Misc_Colon;
        }

        std::string GetName() const override {
            return ":";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        bool Valid() const override {
            if (!left || !right) return false;

            if (left->is_token) {
                if (left->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                switch (left->node->GetType()) {
                    case Type::OP_Dot:
                        if (!left->node->Valid()) return false;
                        break;
                    
                    case Type::Struct_Curly:
                        {
                            if (!left->node->Valid()) return false;
                            auto curly = std::static_pointer_cast<StructCurlyTreeNode>(left->node);

                            if (curly->inside->size() == 0) return false;

                            Tree tree = curly->inside;

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
                        }
                        break;
                    
                    default:
                        return false;
                }
            }

            if (right->is_token) {
                if (right->token->GetType() != TokenType::Type::Identifier) return false;
            } else {
                switch (right->node->GetType()) {
                    case Type::Misc_Lambda:
                    case Type::Misc_Call:
                    case Type::ClassAccess_Public:
                    case Type::ClassAccess_Private:
                    case Type::ClassAccess_Protected:
                    case Type::Struct_Curly:
                        return right->node->Valid();
                    
                    case Type::Struct_Comma:
                        {
                            if (!right->node->Valid()) return false;
                            auto comma = std::static_pointer_cast<StructCommaTreeNode>(right->node);

                            for (auto it : comma->nodes) {
                                if (it->is_token) return false;
                                switch (it->node->GetType()) {
                                    case Type::ClassAccess_Public:
                                    case Type::ClassAccess_Private:
                                    case Type::ClassAccess_Protected:
                                        break;
                                    
                                    default:
                                        return false;
                                }
                            }
                        }
                        break;

                    default:
                        return false;
                }
            }

            return true;
        }

        const TokenNode left;
        const TokenNode right;
    };

    class ColonTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::SYM_Colon)) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op = TreeNode(new ColonTreeNode(left, right));

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