#include <parse.hpp>

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