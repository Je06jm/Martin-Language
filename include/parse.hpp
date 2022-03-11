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
            Definition_Let,
            Definition_Set,
            Definition_Const,
            Definition_Constexpr,
            Definition_Struct,
            Definition_Union,
            Definition_Enum,
            Definition_Typedef,
            Access_Array,
            Access_Reference,
            Access_Shared,
            Access_Unique,
            Access_Pointer,
            Assignment_Assign,
            Assignment_TypeAssign,
            Assignment_AddAssign,
            Assignment_SubAssign,
            Assignment_MulAssign,
            Assignment_DivAssign,
            Assignment_ModAssign,
            Assignment_PowAssign,
            Assignment_BitAndAssign,
            Assignment_BitOrAssign,
            Assignment_BitXOrAssign,
            Assignment_BitNotAssign,
            Assignment_BitShiftLeftAssign,
            Assignment_BitShiftRightAssign,
            FlowControl_If,
            FlowControl_Elif,
            FlowControl_Else,
            FlowControl_While,
            FlowControl_For,
            FlowControl_Foreach,
            FlowControl_Switch,
            FlowControl_Match,
            FlowControl_Continue,
            FlowControl_Break,
            FlowControl_Return,
            ClassType_Virtual,
            ClassType_Override,
            ClassType_Static,
            ClassAccess_Public,
            ClassAccess_Protected,
            ClassAccess_Private,
            ClassAccess_Friend,
            Misc_FromImport,
            Misc_Arrow,
            Misc_In,
            Misc_Colon,
            Misc_Func,
            Misc_Lambda,
            Misc_Unsafe,
            Misc_Class,
            Misc_Extern,
            Misc_Call
        };

        virtual ~TreeNodeBase() {}
        
        virtual Type GetType() const = 0;
        virtual std::string GetName() const = 0;

        virtual void Serialize(std::string& serial) const {
            serial = "Unimplemented serialize on tree node";
        }

        virtual bool Valid() const {
            return true;
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
            if (!tree)
                Fatal("Trying to get an item on a nullptr tree\n");
            
            if (index >= tree->size())
                return nullptr;

            return (*tree)[index];
        }

        static Token GetIndexOrNullToken(Tree tree, size_t index) {
            if (!tree)
                Fatal("Trying to get an item on a nullptr tree\n");
            
            TokenNode token_node = GetIndexOrNull(tree, index);
            if ((token_node == nullptr) || !token_node->is_token)
                return nullptr;

            return token_node->token;
        }

        static void ReplaceTree(Tree tree, Tree replacement, size_t index, size_t length) {
            if (!tree)
                Fatal("Trying to erase items on a nullptr tree\n");
            else if (index >= tree->size())
                Fatal("Trying to erase items starting at $ of a tree of size $\n", index, tree->size());
            else if ((index + length) >= tree->size())
                Fatal("Trying to erase $ items starting at $ of a tree of size $\n", length, index, tree->size());

            tree->erase(tree->begin() + index, tree->begin() + index + length);
            tree->insert(tree->begin() + index, replacement->begin(), replacement->end());
        }

        static void ReplaceTreeWithTokenNode(Tree tree, TokenNode replacement, size_t index, size_t length) {
            if (!tree)
                Fatal("Trying to erase items on a nullptr tree\n");
            else if (index >= tree->size())
                Fatal("Trying to erase items starting at $ of a tree of size $\n", index, tree->size());
            else if ((index + length) > tree->size())
                Fatal("Trying to erase $ items starting at $ of a tree of size $\n", length, index, tree->size());

            tree->erase(tree->begin() + index, tree->begin() + index + length);
            tree->insert(tree->begin() + index, replacement);
        }

        static void RemoveTreeIndex(Tree tree, size_t index) {
            if (!tree)
                Fatal("Trying to erase an item on a nullptr tree\n");
            if (index >= tree->size())
                Fatal("Trying to erase item $ of a tree of size $\n", index, tree->size());;
            
            tree->erase(tree->begin() + index);
        }
    };

    class Parser {
    public:
        Parser();

        Tree ParseFile(const std::string& path, std::string& error_msg);
        Tree ParseString(const std::string& code, std::string& error_msg);

        Tree ParseTokens(TokenList tokens);
    
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