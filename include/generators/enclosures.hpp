#ifndef MARTIN_GENERATORS_ENCLOSURES
#define MARTIN_GENERATORS_ENCLOSURES

#include <parse.hpp>

#include <vector>

namespace Martin {

    class StructParenthesesTreeNode : public TreeNodeBase {
    public:
        StructParenthesesTreeNode(Tree inside) : inside(inside) {}

        Type GetType() const override {
            return Type::Struct_Parentheses;
        }

        std::string GetName() const override {
            return "()";
        }

        void Serialize(std::string& serial) const override {
            serial = GetName() + "(";
            std::string s;
            for (auto it : *inside) {
                it->Serialize(s);
                serial += s;
            }
            serial += ")";
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!inside) return false;

            for (auto it : (*inside)) {
                if (!it->is_token) {
                    if (!it->node->Valid()) return false;
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            for (auto node : *inside) {
                if (!node->is_token) {
                    if (node->node->GetType() == type) {
                        list.push_back(node->node);
                    }
                    auto list2 = node->node->GetAllNodesOfType(type);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
            }

            return list;
        }

        const Tree inside;
    };

    class StructCurlyTreeNode : public TreeNodeBase {
    public:
        StructCurlyTreeNode(Tree inside) : inside(inside) {}

        Type GetType() const override {
            return Type::Struct_Curly;
        }

        std::string GetName() const override {
            return "{}";
        }

        void Serialize(std::string& serial) const override {
            serial = GetName() + "(";
            std::string s;
            for (auto it : *inside) {
                it->Serialize(s);
                serial += s;
            }
            serial += ")";
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!inside) return false;

            for (auto it : (*inside)) {
                if (!it->is_token) {
                    if (!it->node->Valid()) return false;
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            for (auto node : *inside) {
                if (!node->is_token) {
                    if (node->node->GetType() == type) {
                        list.push_back(node->node);
                    }
                    auto list2 = node->node->GetAllNodesOfType(type);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
            }

            return list;
        }

        const Tree inside;
    };

    class StructBracketTreeNode : public TreeNodeBase {
    public:
        StructBracketTreeNode(Tree inside) : inside(inside) {}

        Type GetType() const override {
            return Type::Struct_Bracket;
        }

        std::string GetName() const override {
            return "[]";
        }

        void Serialize(std::string& serial) const override {
            serial = GetName() + "(";
            std::string s;
            for (auto it : *inside) {
                it->Serialize(s);
                serial += s;
            }
            serial += ")";
        }

        bool Valid() const override {
            if (!NodeValid()) {
                Fatal("Node $ is invalid on line $\n", GetName(), GetLineNumber());
            }
            return true;
        }

        bool NodeValid() const {
            if (!inside) return false;

            for (auto it : (*inside)) {
                if (!it->is_token) {
                    if (!it->node->Valid()) return false;
                }
            }

            return true;
        }

        std::vector<TreeNode> GetAllNodesOfType(Type type) const override {
            std::vector<TreeNode> list;

            for (auto node : *inside) {
                if (!node->is_token) {
                    if (node->node->GetType() == type) {
                        list.push_back(node->node);
                    }
                    auto list2 = node->node->GetAllNodesOfType(type);
                    list.insert(list.end(), list2.begin(), list2.end());
                }
            }

            return list;
        }

        const Tree inside;
    };

    class StructEnclosuresTreeGenerator : public TreeNodeGenerator {
    public:
        size_t ProcessBranch(Tree tree, size_t index, size_t end) override {
            Token sym = GetIndexOrNullToken(tree, index);
            if (sym && (
                (sym->GetType() == TokenType::Type::SYM_OpenCurly) ||
                (sym->GetType() == TokenType::Type::SYM_OpenBracket) ||
                (sym->GetType() == TokenType::Type::SYM_OpenParentheses)
            )) {
                TokenType::Type opener, closer;
                opener = sym->GetType();

                switch (opener) {
                    case TokenType::Type::SYM_OpenCurly:
                        closer = TokenType::Type::SYM_CloseCurly;
                        break;
                    
                    case TokenType::Type::SYM_OpenBracket:
                        closer = TokenType::Type::SYM_CloseBracket;
                        break;
                    
                    case TokenType::Type::SYM_OpenParentheses:
                        closer = TokenType::Type::SYM_CloseParentheses;
                        break;
                }

                size_t closer_pos = index;
                int counter = 0;
                Token other_sym;
                for (size_t i = index + 1; i < end; i++) {
                    other_sym = GetIndexOrNullToken(tree, i);

                    if (other_sym->GetType() == opener)
                        counter++;
                    
                    else if (other_sym->GetType() == closer)
                        counter--;
                    
                    if (counter < 0) {
                        size_t before = tree->size();
                        Tree new_tree = Tree(new std::vector<TokenNode>);
                        new_tree->insert(new_tree->begin(), tree->begin() + index + 1, tree->begin() + i);
                        tree->erase(tree->begin() + index + 1, tree->begin() + i);
                        RemoveTreeIndex(tree, index+1);
                        RemoveTreeIndex(tree, index);
                        size_t shrinked = before - tree->size();

                        ParserSingleton.ParseBranch(new_tree, 0, new_tree->size());

                        TreeNode op;

                        switch (opener) {
                            case TokenType::Type::SYM_OpenCurly:
                                op = TreeNode(new StructCurlyTreeNode(new_tree));
                                break;
                            
                            case TokenType::Type::SYM_OpenBracket:
                                op = TreeNode(new StructBracketTreeNode(new_tree));
                                break;
                            
                            case TokenType::Type::SYM_OpenParentheses:
                                op = TreeNode(new StructParenthesesTreeNode(new_tree));
                                break;
                        }

                        op->SetLineNumber(sym->GetLineNumber());

                        TokenNode token_node = TokenNode(new TokenNodeBase);
                        token_node->node = op;

                        tree->insert(tree->begin() + index, token_node);

                        return shrinked;
                    }
                }
            }
            return 0;
        }
    };

}

#endif