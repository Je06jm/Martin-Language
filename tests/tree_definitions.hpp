#ifndef MARTIN_TEST_TREE_DEFINITIONS
#define MARTIN_TEST_TREE_DEFINITIONS

#include "testing.hpp"

#include <generators/definitions.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_definitions : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Definitions)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a Int32");

            if (!ValidateTokenList(tree, error, 2)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);
            TokenNode int32 = GetTokenNodeFromTokenList(tree, 1);

            std::vector<Token> ids;
            ids.push_back(a->token);

            SUBTEST_TREE("let a : Int32", ids, int32, LetTreeNode, true);
            SUBTEST_TREE("set a : Int32", ids, int32, SetTreeNode, true);
            SUBTEST_TREE("const a : Int32", ids, int32, ConstTreeNode, true);
            SUBTEST_TREE("constexpr a : Int32", ids, int32, ConstexprTreeNode, true);

            TokenNode types;

            {
                auto tree2 = ParserSingleton.ParseString("{Int32, Float32}", error);
                types = (*tree2)[0];
            }

            SUBTEST_TREE("let a : {Int32, Float32}", ids, types, LetTreeNode, true);
            SUBTEST_TREE("set a : {Int32, Float32}", ids, types, SetTreeNode, true);
            SUBTEST_TREE("const a : {Int32, Float32}", ids, types, ConstTreeNode, true);
            SUBTEST_TREE("constexpr a : {Int32, Float32}", ids, types, ConstexprTreeNode, true);

            return true;
        }
    };
}
#endif