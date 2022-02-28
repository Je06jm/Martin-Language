#ifndef MARTIN_PARSE
#define MARTIN_PARSE

#include <vector>
#include <memory>
#include <string>

#include <tokens.hpp>
#include <values.hpp>
#include <logging.hpp>

namespace Martin {

    class TreeNodeBase;
    class TreeNodeGenerator;
    typedef struct _TokenNodeBase TokenNodeBase;

    typedef std::shared_ptr<TokenNodeBase> TokenNode;
    typedef std::shared_ptr<std::vector<TokenNode>> Tree;

    typedef std::shared_ptr<TreeNodeBase> TreeNode;

    typedef std::shared_ptr<TreeNodeGenerator> TreeGenerator;

    class TreeNodeBase {
    public:
        enum class Type {
            OP_Add,
            OP_Sub,
            OP_Mul,
            OP_Div,
            OP_Mod,
            OP_Pow,
            OP_BitAnd,
            OP_BitOr,
            OP_BitXOr,
            OP_BitNot,
            OP_BitShiftLeft,
            OP_BitShiftRight,
            OP_Equals,
            OP_NotEquals,
            OP_GreaterThan,
            OP_LessThan,
            OP_GreaterThanEquals,
            OP_LessThanEquals,
            OP_LogicalAnd,
            OP_LogicalOr,
            OP_LogicalNot,
            OP_Dot,
            Struct_Parentheses,
            Struct_Curly,
            Struct_Bracket,
            Struct_As,
            Struct_Comma,
            Misc_FromImport
        };

        virtual ~TreeNodeBase() {}
        
        virtual Type GetType() const = 0;
        virtual std::string GetName() const = 0;

        virtual void Serialize(std::string& serial) const {
            serial = "Unimplemented serialize on tree node";
        }
    };

    struct _TokenNodeBase {
        // Won't compile without these
        _TokenNodeBase() {}
        ~_TokenNodeBase() {}

        void Serialize(std::string& serial) const {
            if (is_token) {
                serial = token->GetName();
            } else {
                std::string s;
                node->Serialize(serial);
            }
        }

        TreeNode node;
        Token token;

        bool is_token = false;
    };


    class TreeNodeGenerator {
    public:
        virtual ~TreeNodeGenerator() {}

        virtual bool IsReversed() const {
            return false;
        }

        virtual size_t ProcessBranch(Tree tree, size_t index, size_t end) = 0;

        virtual void Serialize(std::string& serial) const {
            serial = "Unimplemented serialize on tree generator";
        };

    protected:
        static TokenNode GetIndexOrNull(Tree tree, size_t index) {
            if (index >= tree->size())
                return nullptr;

            return (*tree)[index];
        }

        static Token GetIndexOrNullToken(Tree tree, size_t index) {
            TokenNode token_node = GetIndexOrNull(tree, index);
            if ((token_node == nullptr) || !token_node->is_token)
                return nullptr;

            return token_node->token;
        }

        static void ReplaceTree(Tree tree, Tree replacement, size_t index, size_t length) {
            tree->erase(tree->begin() + index, tree->begin() + index + length);
            tree->insert(tree->begin() + index, replacement->begin(), replacement->end());
        }

        static void ReplaceTreeWithTokenNode(Tree tree, TokenNode replacement, size_t index, size_t length) {
            tree->erase(tree->begin() + index, tree->begin() + index + length);
            tree->insert(tree->begin() + index, replacement);
        }

        static void RemoveTreeIndex(Tree tree, size_t index) {
            tree->erase(tree->begin() + index);
        }
    };

    class Parser {
    public:
        Parser();

        Tree ParseTokens(TokenList tokens, std::string& error_msg);
    
        void ParseBranch(Tree tree, size_t start, size_t end);

        void Serialize(std::string& serial) const {
            serial = Format("Parser with $ generators", generators.size());
        }

    private:
        std::vector<TreeGenerator> generators;
    };

    extern Parser ParserSingleton;

}

#endif