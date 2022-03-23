#ifndef MARTIN_GENERATORS_IN
#define MARTIN_GENERATORS_IN

#include <parse.hpp>

namespace Martin {

    class InTreeNode : public TreeNodeBase {
    public:
        InTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::Misc_In;
        }

        std::string GetName() const override {
            return "In";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
            
        }

        const TokenNode left;
        const TokenNode right;
    };

    class InTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);

            if (sym && (sym->GetType() == TokenType::Type::KW_In)) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op = TreeNode(new InTreeNode(left, right));

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