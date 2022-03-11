#ifndef MARTIN_GENERATORS_CLASS
#define MARTIN_GENERATORS_CLASS

#include <parse.hpp>

namespace Martin {

    class ClassTreeNode : public TreeNodeBase {
    public:
        ClassTreeNode(TokenNode name,TokenNode scope) : name(name), scope(scope) {}

        Type GetType() const override {
            return Type::Misc_Class;
        }

        std::string GetName() const override {
            return "Class";
        }

        void Serialize(std::string& serial) const override {
            if (scope)
                serial = Format("$($, $)", GetName(), *name, *scope);
            
            else
                serial = Format("$($, nullptr)", *name, GetName());
        }

        const TokenNode name;
        const TokenNode scope;    
    };

    class ClassTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (sym->GetType() == TokenType::Type::KW_Class)) {
                TokenNode name = GetIndexOrNull(tree, index+1);
                TokenNode scope = GetIndexOrNull(tree, index+2);

                if (name && scope) {
                    TreeNode op = TreeNode(new ClassTreeNode(name, scope));

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

#endif