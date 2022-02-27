#include <parse.hpp>

#include <vector>

namespace Martin {

    class StructParenthesesTreeNode : public TreeNodeBase {
    public:
        StructParenthesesTreeNode(const std::vector<TokenNode>& inside) : inside(inside) {}

        Type GetType() const override {
            return Type::Struct_Parentheses;
        }

        std::string GetName() const override {
            return "()";
        }

        const std::vector<TokenNode> inside;
    };

    class StructCurlyTreeNode : public TreeNodeBase {
    public:
        StructCurlyTreeNode(const std::vector<TokenNode>& inside) : inside(inside) {}

        Type GetType() const override {
            return Type::Struct_Curly;
        }

        std::string GetName() const override {
            return "{}";
        }

        const std::vector<TokenNode> inside;
    };

    class StructBracketTreeNode : public TreeNodeBase {
    public:
        StructBracketTreeNode(const std::vector<TokenNode>& inside) : inside(inside) {}

        Type GetType() const override {
            return Type::Struct_Bracket;
        }

        std::string GetName() const override {
            return "[]";
        }

        const std::vector<TokenNode> inside;
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
                        ParserSingleton.ParseBranch(tree, index + 1, i - 1);
                        size_t shrinked = before - tree->size();

                        RemoveTreeIndex(tree, index);
                        RemoveTreeIndex(tree, i - shrinked - 1);

                        return shrinked + 2;
                    }
                }
            }
            return 0;
        }
    };

}