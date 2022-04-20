#ifndef MARTIN_TEST_TREE_FUNCLAMBDA
#define MARTIN_TEST_TREE_FUNCLAMBDA

#include "testing.hpp"

#include <generators/funclambda.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_funclambda : public Test {
    public:
        std::string GetName() const override {
            return "Tree(FuncLambda)";
        }

        bool RunTest() override {
            auto tree = ParserSingleton.ParseString("a() -> None", error);
            auto tree2 = ParserSingleton.ParseString("() -> None", error);
            auto tree3 = ParserSingleton.ParseString("{}", error);

            if (!ValidateParserTree(tree, error, 1)) return false;
            if (!ValidateParserTree(tree, error, 1)) return false;
            if (!ValidateParserTree(tree3, error, 1)) return false;

            TokenNode arrow_call = GetTokenNodeFromParseList(tree, 0);
            TokenNode arrow = GetTokenNodeFromParseList(tree2, 0);
            TokenNode scope = GetTokenNodeFromParseList(tree3, 0);

            SUBTEST_TREE("func a() -> None {}", arrow_call, scope, FuncTreeNode, true);
            SUBTEST_TREE("lambda() -> None {}", arrow, scope, LambdaTreeNode, true);

            return true;
        }
    };
}
#endif