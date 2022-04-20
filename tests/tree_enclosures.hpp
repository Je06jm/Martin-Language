#ifndef MARTIN_TEST_TREE_ENCLOSURES
#define MARTIN_TEST_TREE_ENCLOSURES

#include "testing.hpp"

#include <generators/enclosures.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_enclosures : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Enclosures)";
        }

        bool RunTest() override {
            auto tree = ParserSingleton.ParseString("a, b", error);

            if (!ValidateParserTree(tree, error, 1)) return false;
            
            SUBTEST_TREE_SINGLE("(a, b)", tree, StructParenthesesTreeNode, true);
            SUBTEST_TREE_SINGLE("{a, b}", tree, StructCurlyTreeNode, true);
            SUBTEST_TREE_SINGLE("[a, b]", tree, StructBracketTreeNode, true);

            return true;
        }
    };
}
#endif