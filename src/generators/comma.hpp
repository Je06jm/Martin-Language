#ifndef MARTIN_GENERATORS_COMMA
#define MARTIN_GENERATORS_COMMA

#include <parse.hpp>

namespace Martin {

    class StructCommaTreeNode : public TreeNodeBase {
    public:
        StructCommaTreeNode(const std::vector<TokenNode>& nodes) : nodes(nodes) {}

        Type GetType() const override {
            return Type::Struct_Comma;
        }

        std::string GetName() const override {
            return ",";
        }

        void Serialize(std::string& serial) const override {
            serial = GetName() + "(";
            for (auto it : nodes) {
                serial += Format("$, ", *it);
            }

            serial = serial.substr(0, serial.size() - 2);
            serial += ")";
        }

        bool Valid() const override {
            if (nodes.size() == 0) return false;

            for (auto it : nodes) {
                if (it->is_token) {
                    switch (it->token->GetType()) {
                        case TokenType::Type::Identifier:
                        case TokenType::Type::Integer:
                        case TokenType::Type::UInteger:
                        case TokenType::Type::FloatingSingle:
                        case TokenType::Type::FloatingDouble:
                        case TokenType::Type::Boolean:
                        case TokenType::Type::String8:
                        case TokenType::Type::String16l:
                        case TokenType::Type::String32l:
                        case TokenType::Type::String16b:
                        case TokenType::Type::String32b:
                            break;
                        
                        default:
                            return false;
                    }
                } else {
                    switch (it->node->GetType()) {
                        case Type::Misc_Call:
                        case Type::OP_Dot:
                        case Type::Misc_Lambda:
                        case Type::Struct_Parentheses:
                        case Type::ClassAccess_Public:
                        case Type::ClassAccess_Private:
                        case Type::ClassAccess_Protected:
                            break;
                        
                        default:
                            return false;
                    }
                }
            }

            return true;
        }

        const std::vector<TokenNode> nodes;
    };

    class StructCommaTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::SYM_Comma)) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    if (!left->is_token && (left->node->GetType() == TreeNodeBase::Type::Struct_Comma)) {
                        std::vector<TokenNode> nodes;
                        auto comma_node = std::dynamic_pointer_cast<StructCommaTreeNode>(left->node);
                        nodes.insert(nodes.begin(), comma_node->nodes.begin(), comma_node->nodes.end());
                        nodes.push_back(right);

                        TreeNode op = TreeNode(new StructCommaTreeNode(nodes));

                        TokenNode token_node = TokenNode(new TokenNodeBase);
                        token_node->node = op;
                        ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                        return 3;
                    } else {
                        std::vector<TokenNode> nodes;
                        nodes.push_back(left);
                        nodes.push_back(right);

                        TreeNode op = TreeNode(new StructCommaTreeNode(nodes));

                        TokenNode token_node = TokenNode(new TokenNodeBase);
                        token_node->node = op;
                        ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                        return 3;
                    }
                }
            }
            return 0;
        }
    };

}

#endif