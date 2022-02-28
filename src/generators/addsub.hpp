#include <parse.hpp>

#include <logging.hpp>

#include "typehelper.hpp"

namespace Martin {

    class OPAddTreeNode : public TreeNodeBase {
    public:
        OPAddTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Add;
        }

        std::string GetName() const override {
            return "+";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }
    
    private:
        const TokenNode left;
        const TokenNode right;
    };

    class OPSubTreeNode : public TreeNodeBase {
    public:
        OPSubTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Sub;
        }

        std::string GetName() const override {
            return "-";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
            TokenNode left;
            TokenNode right;
    };

    class OPAddSubTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_Add) ||
                (sym->GetType() == TokenType::Type::SYM_Sub)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op;

                    if (sym->GetType() == TokenType::Type::SYM_Add)
                        op = TreeNode(new OPAddTreeNode(left, right));
                    
                    else
                        op = TreeNode(new OPSubTreeNode(left, right));
                        
                    TokenNode token_node = TokenNode(new TokenNodeBase);
                    token_node->node = op;
                    ReplaceTreeWithTokenNode(tree, token_node, index-1, 3);

                    return 3;
                }
            } else if (sym && (sym->GetType() == TokenType::Type::Integer)) {
                // Do something here? The tokenizer probably converted 1-2 into
                // Integer 1, Integer -2
            }

            return 0;
        }
    };

}