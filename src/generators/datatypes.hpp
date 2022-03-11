#ifndef MARTIN_GENERATORS_DATATYPE
#define MARTIN_GENERATORS_DATATYPE

#include <parse.hpp>

namespace Martin {

    class StructTreeNode : public TreeNodeBase {
    public:
        StructTreeNode(TokenNode name, TokenNode members) : name(name), members(members)  {}

        Type GetType() const override {
            return Type::Definition_Struct;
        }

        std::string GetName() const override {
            return "Struct";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *name, *members);
            
        }

        const TokenNode name;
        const TokenNode members;    
    };

    class UnionTreeNode : public TreeNodeBase {
    public:
        UnionTreeNode(TokenNode name, TokenNode members) : name(name), members(members)  {}

        Type GetType() const override {
            return Type::Definition_Union;
        }

        std::string GetName() const override {
            return "Union";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *name, *members);
        }

        const TokenNode name;
        const TokenNode members;    
    };

    class EnumTreeNode : public TreeNodeBase {
    public:
        EnumTreeNode(TokenNode name, TokenNode members) : name(name), members(members)  {}

        Type GetType() const override {
            return Type::Definition_Enum;
        }

        std::string GetName() const override {
            return "Enum";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($, $)", GetName(), *name, *members);
            
        }

        const TokenNode name;
        const TokenNode members;    
    };

    class DataTypesTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::KW_Struct) ||
                (sym->GetType() == TokenType::Type::KW_Union) ||
                (sym->GetType() == TokenType::Type::KW_Enum)
            )) {
                TokenNode id = GetIndexOrNull(tree, index+1);
                TokenNode members = GetIndexOrNull(tree, index+2);

                if (id && members) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Struct:
                            op = TreeNode(new StructTreeNode(id, members));
                            break;
                        
                        case TokenType::Type::KW_Union:
                            op = TreeNode(new UnionTreeNode(id, members));
                            break;
                        
                        case TokenType::Type::KW_Enum:
                            op = TreeNode(new UnionTreeNode(id, members));
                            break;
                    }

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