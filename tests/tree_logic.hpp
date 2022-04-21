#ifndef MARTIN_TEST_TREE_LOGIC
#define MARTIN_TEST_TREE_LOGIC

#include "testing.hpp"

#include <generators/logical.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_logic : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Logic)";
        }

        bool RunTest() override {
            auto tree = ParserSingleton.ParseString("true a() b c==d", error);

            if (!ValidateParserTree(tree, error, 4)) return false;

            TokenNode lt_true = (*tree)[0];
            TokenNode call = (*tree)[1];
            TokenNode b = (*tree)[2];
            TokenNode equals = (*tree)[3];

            SUBTEST_TREE("true and a()", lt_true, call, OPLogicalAndTreeNode, true);
            SUBTEST_TREE("b and c==d", b, equals, OPLogicalAndTreeNode, true);

            SUBTEST_TREE("true or a()", lt_true, call, OPLogicalOrTreeNode, true);
            SUBTEST_TREE("b or c==d", b, equals, OPLogicalOrTreeNode, true);

            SUBTEST_TREE_SINGLE("not true", lt_true, OPLogicalNotTreeNode, true);
            SUBTEST_TREE_SINGLE("not a()", call, OPLogicalNotTreeNode, true);
            SUBTEST_TREE_SINGLE("not b", b, OPLogicalNotTreeNode, true);
            SUBTEST_TREE_SINGLE("not c==d", equals, OPLogicalNotTreeNode, true);

            return true;
        }
    };
}
#endif