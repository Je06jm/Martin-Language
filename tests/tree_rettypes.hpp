#ifndef MARTIN_TEST_TREE_RETTYPES
#define MARTIN_TEST_TREE_RETTYPES

#include "testing.hpp"

#include <generators/rettypes.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_rettypes : public Test {
    public:
        std::string GetName() const override {
            return "Tree(RetTypes)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a");

            if (!ValidateTokenList(tree, error, 1)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);

            SUBTEST_TREE_SINGLE("let a", a->token, LetRetTypeTreeNode, true);
            SUBTEST_TREE_SINGLE("set a", a->token, SetRetTypeTreeNode, true);
            SUBTEST_TREE_SINGLE("const a", a->token, ConstRetTypeTreeNode, true);
            SUBTEST_TREE_SINGLE("constexpr a", a->token, ConstexprRetTypeTreeNode, true);

            return true;
        }
    };
}
#endif