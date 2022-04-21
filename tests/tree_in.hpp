#ifndef MARTIN_TEST_TREE_IN
#define MARTIN_TEST_TREE_IN

#include "testing.hpp"

#include <generators/in.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_in : public Test {
    public:
        std::string GetName() const override {
            return "Tree(In)";
        }

        bool RunTest() override {
            auto tree = ParserSingleton.ParseString("a.b.c d", error);

            if (!ValidateParserTree(tree, error, 2)) return false;

            TokenNode dot = (*tree)[0];
            TokenNode d = (*tree)[1];

            SUBTEST_TREE("d in d", d, d, InTreeNode, true);
            SUBTEST_TREE("a.b.c in d", dot, d, InTreeNode, true);
            SUBTEST_TREE("d in a.b.c", d, dot, InTreeNode, true);
            SUBTEST_TREE("a.b.c in a.b.c", dot, dot, InTreeNode, true);

            return true;
        }
    };
}
#endif