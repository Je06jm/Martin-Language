#ifndef MARTIN_TEST_TREE_CLASS
#define MARTIN_TEST_TREE_CLASS

#include "testing.hpp"

#include <generators/class.hpp>
#include <generators/classaccess.hpp>
#include <generators/enclosures.hpp>
#include <generators/colon.hpp>

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
    class Test_tree_class : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Class)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("class a b");

            if (!ValidateTokenList(tree, error, 3)) return false;

            TokenNode token_node_class = GetTokenNodeFromTokenList(tree, 0);
            TokenNode a = GetTokenNodeFromTokenList(tree, 1);
            TokenNode b = GetTokenNodeFromTokenList(tree, 2);

            TokenNode colon, scope;

            {
                TreeNode tree_class = TreeNode(new ClassAccessPublicTreeNode(b));
                TokenNode kw_public = TokenNode(new TokenNodeBase);
                kw_public->node = tree_class;

                TreeNode tree_colon = TreeNode(new ColonTreeNode(a, kw_public));
                colon = TokenNode(new TokenNodeBase);
                colon->node = tree_colon;

                auto tree2 = ParserSingleton.ParseString("", error);

                TreeNode curly = TreeNode(new StructCurlyTreeNode(tree2));
                scope = TokenNode(new TokenNodeBase);
                scope->node = curly;
            }

            SUBTEST("class a {}", a, scope, ClassTreeNode, true);
            SUBTEST("class a : public b {}", colon, scope, ClassTreeNode, true);
            SUBTEST("class {} a", scope, a, ClassTreeNode, false);
            SUBTEST("class a a", a, a, ClassTreeNode, false);
            SUBTEST("class public b : a {}", colon, a, ClassTreeNode, false);

            return true;
        }
    };
}

#undef SUBTEST

#endif