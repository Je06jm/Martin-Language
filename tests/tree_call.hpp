#ifndef MARTIN_TEST_TREE_CALL
#define MARTIN_TEST_TREE_CALL

#include "testing.hpp"

#include <generators/call.hpp>
#include <generators/enclosures.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

#define SUBTEST(str, left, right, type, valid)\
{\
    type node(left, right);\
    if (node.Valid()) {\
        if (!valid) {\
            error = ParseNodeError("valid", str);\
            return false;\
        }\
    } else if (valid) {\
        error = ParseNodeError("not valid", str);\
        return false;\
    }\
}

namespace Martin {
    class Test_tree_call : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Call)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a");

            if (!ValidateTokenList(tree, error, 1)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);

            TokenNode args;

            {
                auto tree2 = ParserSingleton.ParseString("b", error);

                TreeNode op = TreeNode(new StructParenthesesTreeNode(tree2));

                args = TokenNode(new TokenNodeBase);
                args->node = op;
            }

            SUBTEST("a(b)", a->token, args, CallTreeNode, true);
            SUBTEST("nullptr(b)", nullptr, args, CallTreeNode, false);
            SUBTEST("a(nullptr)", a->token, nullptr, CallTreeNode, false);
            SUBTEST("nullptr(nullptr)", nullptr, nullptr, CallTreeNode, false);

            return true;
        }
    };
}

#undef SUBTEST

#endif