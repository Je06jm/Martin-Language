#ifndef MARTIN_TEST_TREE_FLOWCONTROLS
#define MARTIN_TEST_TREE_FLOWCONTROLS

#include "testing.hpp"

#include <generators/flowcontrols.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

#define SUBTEST_TREE_MULTIPLE(str, start, condition, increment, scope, type, valid)\
{\
    type node(start, condition, increment, scope);\
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
    class Test_tree_flowcontrols : public Test {
    public:
        std::string GetName() const override {
            return "Tree(FlowControls)";
        }

        bool RunTest() override {
            TokenNode if_condition;
            TokenNode a;
            TokenNode scope, colon_scope, switch_scope;
            TokenNode for_start, for_condition, for_increment;
            TokenNode foreach;
            for_start = if_condition;

            {
                auto tree = TokenizerSingleton.TokenizeString("true ");
                if (!ValidateTokenList(tree, error, 1)) return false;
                if_condition = GetTokenNodeFromTokenList(tree, 0);
            }

            {
                auto tree = TokenizerSingleton.TokenizeString("a");
                if (!ValidateTokenList(tree, error, 1)) return false;
                a = GetTokenNodeFromTokenList(tree, 0);
            }

            {
                auto tree = ParserSingleton.ParseString("{let a : Int32 = 3}", error);
                if (!ValidateParserTree(tree, error, 1)) return false;
                scope = (*tree)[0];
            }

            {
                auto tree = ParserSingleton.ParseString("{Int32: a Float32: lambda() -> None {}}", error);
                if (!ValidateParserTree(tree, error, 1)) return false;
                colon_scope = (*tree)[0];
            }

            {
                auto tree = ParserSingleton.ParseString("{IS_A: {Print(a) break} default: {Print(b)}}", error);
                if (!ValidateParserTree(tree, error, 1)) return false;
                switch_scope = (*tree)[0];
            }

            {
                auto tree = ParserSingleton.ParseString("a < 4", error);
                if (!ValidateParserTree(tree, error, 1)) return false;
                for_condition = (*tree)[0];
            }

            {
                auto tree = ParserSingleton.ParseString("a += 1", error);
                if (!ValidateParserTree(tree, error, 1)) return false;
                for_increment = (*tree)[0];
            }

            {
                auto tree = ParserSingleton.ParseString("let a : Any in b", error);
                if (!ValidateParserTree(tree, error, 1)) return false;
                foreach = (*tree)[0];
            }

            SUBTEST_TREE("if (true) {let a : Int32 = 3}", if_condition, scope, FlowControlIfTreeNode, true);
            SUBTEST_TREE("elif (true) {let a : Int32 = 3}", if_condition, scope, FlowControlElifTreeNode, true);
            SUBTEST_TREE_SINGLE("else {let a : Int32 = 3}", scope, FlowControlElseTreeNode, true);
            SUBTEST_TREE("while (true) {let a : Int32 = 3}", if_condition, scope, FlowControlWhileTreeNode, true);
            SUBTEST_TREE_MULTIPLE("for (let a : Int32 = 0, a < 4, a += a) {let a : Int32 = 3}", for_start, for_condition, for_increment, scope, FlowControlForTreeNode, true);
            SUBTEST_TREE("foreach (let a : Any in b)", foreach, scope, FlowControlForeachTreeNode, true);
            SUBTEST_TREE("match (a) {Int32: a Float32: lambda b() -> None {}}", a, colon_scope, FlowControlMatchTreeNode, true);
            SUBTEST_TREE("switch (a) {IS_A: {Print(a) break} default: {Print(b) return None}}", a, switch_scope, FlowControlSwitchTreeNode, true);
            SUBTEST_TREE_SINGLE("return a", a, FlowControlReturnTreeNode, true);

            return true;
        }
    };
}

#undef SUBTEST_TREE_MULTIPLE

#endif