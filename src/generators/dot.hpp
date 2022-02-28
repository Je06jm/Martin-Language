#include <parse.hpp>

namespace Martin {

    class OPDotTreeNode : public TreeNodeBase {
    public:
        OPDotTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Dot;
        }

        std::string GetName() const override {
            return ".";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

        const TokenNode left;
        const TokenNode right;
    };

    class OPDotTreeGenerator : public TreeNodeGenerator {
    public:
        bool IsReversed() const override {
            return true;
        }

        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::SYM_Period)) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op = TreeNode(new OPDotTreeNode(left, right));

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