#ifndef MARTIN_TEST_TREE_MULDIVMOD
#define MARTIN_TEST_TREE_MULDIVMOD

#include "testing.hpp"

#include <generators/muldivmod.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_muldivmod : public Test {
    public:
        std::string GetName() const override {
            return "Tree(MulDivMod)";
        }

        bool RunTest() override {
            auto tree = ParserSingleton.ParseString("1 a b() c.d", error);

            if (!ValidateParserTree(tree, error, 4)) return false;

            TokenNode one = GetTokenNodeFromParseList(tree, 0);
            TokenNode a = GetTokenNodeFromParseList(tree, 1);
            TokenNode b = GetTokenNodeFromParseList(tree, 2);
            TokenNode c_d = GetTokenNodeFromParseList(tree, 3);

            SUBTEST_TREE("1 * a", one, a, OPMulTreeNode, true);
            SUBTEST_TREE("b() * c.d", b, c_d, OPMulTreeNode, true);

            SUBTEST_TREE("1 / a", one, a, OPDivTreeNode, true);
            SUBTEST_TREE("b() / c.d", b, c_d, OPDivTreeNode, true);

            SUBTEST_TREE("1 % a", one, a, OPModTreeNode, true);
            SUBTEST_TREE("b() % c.d", b, c_d, OPModTreeNode, true);

            return true;
        }
    };
}
#endif