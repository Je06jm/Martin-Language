#include <parse.hpp>

namespace Martin {

    class ExternTreeNode : public TreeNodeBase {
    public:
        ExternTreeNode(Token type, TokenNode right) : type(type), right(right) {}

        Type GetType() const override {
            return Type::Misc_Extern;
        }

        std::string GetName() const override {
            return "Extern";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), type->GetName(), *right);
            
        }

        const Token type;
        const TokenNode right;
    };

    class ExternTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Extern)) {
                Token type = GetIndexOrNullToken(tree, index+1);
                TokenNode right = GetIndexOrNull(tree, index+2);

                if (type && right) {
                    TreeNode op = TreeNode(new ExternTreeNode(type, right));

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