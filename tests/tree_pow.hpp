#ifndef MARTIN_TEST_TREE_POW
#define MARTIN_TEST_TREE_POW

#include "testing.hpp"

#include <generators/pow.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_pow : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Pow)";
        }

        bool RunTest() override {
            auto tree = ParserSingleton.ParseString("1 a b() c.d", error);

            if (!ValidateParserTree(tree, error, 4)) return false;

            TokenNode one = GetTokenNodeFromParseList(tree, 0);
            TokenNode a = GetTokenNodeFromParseList(tree, 1);
            TokenNode b = GetTokenNodeFromParseList(tree, 2);
            TokenNode c_d = GetTokenNodeFromParseList(tree, 3);

            SUBTEST_TREE("1 ** a", one, a, OPPowTreeNode, true);
            SUBTEST_TREE("b() ** c.d", b, c_d, OPPowTreeNode, true);

            return true;
        }
    };
}
#endif