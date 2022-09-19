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
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (nodes.size() == 0) return false;

            for (auto it : nodes) {
                if (!it->is_token) {
                    if (!it->node->Valid()) return false;
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            for (auto node : nodes) {
                if (!node->is_token) {
                    if (node->node->GetType() == type) {
                        list.push_back(node->node);
                    }
                    auto list2 = node->node->GetAllNodesOfType(type);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
            }

            return list;
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

                        op->SetLineNumber(sym->GetLineNumber());

                        TokenNode token_node = TokenNode(new TokenNodeBase);
                        token_node->node = op;
                        ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                        return 3;
                    } else {
                        std::vector<TokenNode> nodes;
                        nodes.push_back(left);
                        nodes.push_back(right);

                        TreeNode op = TreeNode(new StructCommaTreeNode(nodes));

                        op->SetLineNumber(sym->GetLineNumber());

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