#ifndef MARTIN_TEST_TREE_DOT
#define MARTIN_TEST_TREE_DOT

#include "testing.hpp"

#include <generators/dot.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_dot : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Dot)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a b");

            if (!ValidateTokenList(tree, error, 2)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);
            TokenNode b = GetTokenNodeFromTokenList(tree, 1);

            SUBTEST_TREE("a.b", a, b, OPDotTreeNode, true);

            return true;
        }
    };
}
#endif