#ifndef MARTIN_TEST_TREE_ARROW
#define MARTIN_TEST_TREE_ARROW

#include "testing.hpp"

#include <generators/arrow.hpp>

#include <tokens.hpp>
#include <parse.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"

namespace Martin {
    class Test_tree_arrow : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Arrow)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a 2");
            auto tree2 = ParserSingleton.ParseString("(1)", error);

            if (!tree2) return false;

            if (!ValidateTokenList(tree, error, 2)) return false;
            if (!ValidateParserTree(tree2, error, 1)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);
            TokenNode two = GetTokenNodeFromTokenList(tree, 1);
            TokenNode para = GetTokenNodeFromParseList(tree2, 0);

            {
                ArrowTreeNode node(para, a);

                if (!node.Valid()) {
                    error = "ArrowTreeNode is not valid when given ((), Token(a))";
                    return false;
                }
            }

            {
                ArrowTreeNode node(para, two);

                if (node.Valid()) {
                    error = "ArrowTreeNode is valid when given ((), Token(2))";
                    return false;
                }
            }

            {
                ArrowTreeNode node(a, para);

                if (node.Valid()) {
                    error = "ArrowTreeNode is valid when given (Token(a), ())";
                    return false;
                }
            }

            {
                ArrowTreeNode node(two, para);

                if (node.Valid()) {
                    error = "ArrowTreeNode is valid when given (Token(2), ())";
                    return false;
                }
            }

            return true;
        }
    };
}
#endif