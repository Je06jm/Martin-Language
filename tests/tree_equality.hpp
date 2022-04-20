#ifndef MARTIN_TEST_TREE_EQUALITY
#define MARTIN_TEST_TREE_EQUALITY

#include "testing.hpp"

#include <generators/equality.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_equality : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Equality)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a true 3");

            if (!ValidateTokenList(tree, error, 3)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);
            TokenNode lt_true = GetTokenNodeFromTokenList(tree, 1);
            TokenNode three = GetTokenNodeFromTokenList(tree, 2);

            SUBTEST_TREE("a == true", a, lt_true, OPEqualsTreeNode, true);
            SUBTEST_TREE("a != true", a, lt_true, OPNotEqualsTreeNode, true);
            SUBTEST_TREE("a < 3", a, three, OPLessThanTreeNode, true);
            SUBTEST_TREE("a > 3", a, three, OPGreaterThanTreeNode, true);
            SUBTEST_TREE("a <= 3", a, three, OPLessThanEqualsTreeNode, true);
            SUBTEST_TREE("a >= 3", a, three, OPLessThanEqualsTreeNode, true);

            return true;
        }
    };
}
#endif