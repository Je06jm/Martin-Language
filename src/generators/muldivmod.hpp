#ifndef MARTIN_GENERATORS_MULDIVMOD
#define MARTIN_GENERATORS_MULDIVMOD

#include <parse.hpp>

namespace Martin {

    class OPMulTreeNode : public TreeNodeBase {
    public:
        OPMulTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Mul;
        }

        std::string GetName() const override {
            return "*";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        TokenNode left;
        TokenNode right;
    };

    class OPDivTreeNode : public TreeNodeBase {
    public:
        OPDivTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Div;
        }

        std::string GetName() const override {
            return "/";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        TokenNode left;
        TokenNode right;
    };

    class OPModTreeNode : public TreeNodeBase {
    public:
        OPModTreeNode(TokenNode left, TokenNode right) : left(left), right(right) {}

        Type GetType() const override {
            return Type::OP_Mod;
        }

        std::string GetName() const override {
            return "%";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *left, *right);
        }

    private:
        TokenNode left;
        TokenNode right;
    };

    class OPMulDivModTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_Mul) ||
                (sym->GetType() == TokenType::Type::SYM_Div) ||
                (sym->GetType() == TokenType::Type::SYM_Mod)
            )) {
                TokenNode left = GetIndexOrNull(tree, index-1);
                TokenNode right = GetIndexOrNull(tree, index+1);

                if (left && right) {
                    TreeNode op;
                    
                    if (sym->GetType() == TokenType::Type::SYM_Mul)
                        op = TreeNode(new OPMulTreeNode(left, right));
                    
                    else if (sym->GetType() == TokenType::Type::SYM_Div)
                        op = TreeNode(new OPDivTreeNode(left, right));
                    
                    else
                        op = TreeNode(new OPModTreeNode(left, right));
                    
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