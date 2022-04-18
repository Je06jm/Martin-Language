#ifndef MARTIN_TEST_TREE_COMMA
#define MARTIN_TEST_TREE_COMMA

#include "testing.hpp"

#include <generators/comma.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_comma : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Comma)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a true 3.15");

            if (!ValidateTokenList(tree, error, 3)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);
            TokenNode tn_true = GetTokenNodeFromTokenList(tree, 1);
            TokenNode three_onefive = GetTokenNodeFromTokenList(tree, 2);

            std::vector<TokenNode> nodes = {a, tn_true, three_onefive};

            SUBTEST_TREE_SINGLE("a, true, 3.15", nodes, StructCommaTreeNode, true);

            return true;
        }
    };
}
#endif