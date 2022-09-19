#ifndef MARTIN_GENERATORS_GETTERSETTER
#define MARTIN_GENERATORS_GETTERSETTER

#include <parse.hpp>

namespace Martin {

    class GetterTreeNode : public TreeNodeBase {
    public:
        GetterTreeNode() {}

        Type GetType() const override {
            return Type::Misc_Getter;
        }

        std::string GetName() const override {
            return "Getter";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$", GetName());
        }
    };

    class SetterTreeNode : public TreeNodeBase {
    public:
        SetterTreeNode() {}

        Type GetType() const override {
            return Type::Misc_Setter;
        }

        std::string GetName() const override {
            return "Setter";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$", GetName());
        }
    };

    class GetterSetterTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);

            if (sym && (
                (sym->GetType() == TokenType::Type::KW_Getter) ||
                (sym->GetType() == TokenType::Type::KW_Setter)
            )) {
                TreeNode op;

                if (sym->GetType() == TokenType::Type::KW_Getter)
                    op = TreeNode(new GetterTreeNode);
                
                else
                    op = TreeNode(new SetterTreeNode);

                op->SetLineNumber(sym->GetLineNumber());
                
                TokenNode token_node = TokenNode(new TokenNodeBase);
                token_node->node = op;
                ReplaceTreeWithTokenNode(tree, token_node, index, 1);

                return 1;
            }
            return 0;
        }
    };

}

#endif