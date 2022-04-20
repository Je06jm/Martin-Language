#ifndef MARTIN_TEST_TREE_COLON
#define MARTIN_TEST_TREE_COLON

#include "testing.hpp"

#include <generators/colon.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_colon : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Colon)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a Int32");
            
            if (!ValidateTokenList(tree, error, 2)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);
            TokenNode int32 = GetTokenNodeFromTokenList(tree, 1);
            TokenNode types;

            {
                auto tree2 = ParserSingleton.ParseString("{Int32, None}", error);
                types = (*tree2)[0];
            }

            SUBTEST_TREE("a : Int32", a, int32, ColonTreeNode, true);
            SUBTEST_TREE("{Int32, None} : a", types, a, ColonTreeNode, true);

            return true;
        }
    };
}
#endif