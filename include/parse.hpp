#ifndef MARTIN_PARSE
#define MARTIN_PARSE

#include <vector>
#include <memory>
#include <string>

#include <tokens.hpp>
#include <values.hpp>

namespace Martin {

    class TreeNodeBase;
    class TreeNodeGenerator;
    typedef struct _TokenNodeBase TokenNodeBase;

    typedef std::shared_ptr<TokenNodeBase> TokenNode;
    typedef std::shared_ptr<std::vector<TokenNode>> Tree;

    typedef std::shared_ptr<TreeNodeBase> TreeNode;

    typedef std::shared_ptr<TreeNodeGenerator> TreeGenerator;

    struct _TokenNodeBase {
        // Won't compile without these
        _TokenNodeBase() {}
        ~_TokenNodeBase() {}

        TreeNode node;
        Token token;

        bool is_token = false;
    };

    class TreeNodeBase {
    public:
        enum class Type {
            OP_Add,
            OP_Sub,
            OP_Mul,
            OP_Div,
            OP_Mod,
            OP_Pow,
            OP_BitShiftLeft,
            OP_BitShiftRight
        };

        virtual ~TreeNodeBase() {}
        
        virtual Type GetType() const = 0;
        virtual std::string GetName() const = 0;
    };


    class TreeNodeGenerator {
    public:
        virtual ~TreeNodeGenerator() {}

        virtual size_t ProcessBranch(Tree tree, size_t index, size_t end) = 0;

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
    };

    class Parser {
    public:
        Parser();

        Tree ParseTokens(TokenList tokens, std::string& error_msg);
    
    private:
        std::vector<TreeGenerator> generators;

        void ParseBranch(Tree tree, size_t start, size_t end);
    };

}

#endif