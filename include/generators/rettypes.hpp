#ifndef MARTIN_GENERATORS_RETTYPES
#define MARTIN_GENERATORS_RETTYPES

#include <parse.hpp>

namespace Martin {

    class LetRetTypeTreeNode : public TreeNodeBase {
    public:
        LetRetTypeTreeNode(Token id) : id(id) {}

        Type GetType() const override {
            return Type::ReturnType_Let;
        }

        std::string GetName() const override {
            return "LetRetType";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), id->GetName());
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!id) return false;

            if (id->GetType() != TokenType::Type::Identifier) return false;

            return true;
        }

        const Token id;
    };

    class SetRetTypeTreeNode : public TreeNodeBase {
    public:
        SetRetTypeTreeNode(Token id) : id(id) {}

        Type GetType() const override {
            return Type::ReturnType_Set;
        }

        std::string GetName() const override {
            return "SetRetType";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), id->GetName());
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!id) return false;

            if (id->GetType() != TokenType::Type::Identifier) return false;

            return true;
        }

        const Token id;
    };

    class ConstRetTypeTreeNode : public TreeNodeBase {
    public:
        ConstRetTypeTreeNode(Token id) : id(id) {}

        Type GetType() const override {
            return Type::ReturnType_Const;
        }

        std::string GetName() const override {
            return "ConstRetType";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), id->GetName());
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!id) return false;

            if (id->GetType() != TokenType::Type::Identifier) return false;

            return true;
        }

        const Token id;
    };

    class ConstexprRetTypeTreeNode : public TreeNodeBase {
    public:
        ConstexprRetTypeTreeNode(Token id) : id(id) {}

        Type GetType() const override {
            return Type::ReturnType_Constexpr;
        }

        std::string GetName() const override {
            return "ConstexprRetType";
        }

        void Serialize(std::string& serial) const override {
            serial = Format("$($)", GetName(), id->GetName());
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!id) return false;

            if (id->GetType() != TokenType::Type::Identifier) return false;

            return true;
        }

        const Token id;
    };

    class RetTypesTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::KW_Let) ||
                (sym->GetType() == TokenType::Type::KW_Set) ||
                (sym->GetType() == TokenType::Type::KW_Const) ||
                (sym->GetType() == TokenType::Type::KW_Constexpr)
            )) {
                Token id = GetIndexOrNullToken(tree, index+1);

                if (id->GetType() == TokenType::Type::Identifier) {
                    TreeNode op;

                    switch (sym->GetType()) {
                        case TokenType::Type::KW_Let:
                            op = TreeNode(new LetRetTypeTreeNode(id));
                            break;
                        
                        case TokenType::Type::KW_Set:
                            op = TreeNode(new SetRetTypeTreeNode(id));
                            break;
                        
                        case TokenType::Type::KW_Const:
                            op = TreeNode(new ConstRetTypeTreeNode(id));
                            break;
                        
                        case TokenType::Type::KW_Constexpr:
                            op = TreeNode(new ConstexprRetTypeTreeNode(id));
                            break;
                    }

                    op->SetLineNumber(sym->GetLineNumber());

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

#endif