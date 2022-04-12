#ifndef MARTIN_TEST_TREE_AS
#define MARTIN_TEST_TREE_AS

#include "testing.hpp"

#include <generators/as.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_tree_as : public Test {
    public:
        std::string GetName() const override {
            return "Tree(As)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("1 b c");

            if (!ValidateTokenList(tree, error, 3)) return false;

            TokenNode one = GetTokenNodeFromTokenList(tree, 0);
            TokenNode b = GetTokenNodeFromTokenList(tree, 1);
            TokenNode c = GetTokenNodeFromTokenList(tree, 2);

            {
                StructAsTreeNode node(b, c);

                if (!node.Valid()) {
                    error = ParseNodeError("not valid", "b as c");
                    return false;
                }
            }

            {
                StructAsTreeNode node(one, b);

                if (node.Valid()) {
                    error = ParseNodeError("valid", "1 as b");
                    return false;
                }
            }

            {
                StructAsTreeNode node(c, one);
                
                if (node.Valid()) {
                    error = ParseNodeError("valid", "c as 1");
                    return false;
                }
            }

            {
                TreeNode node1 = TreeNode(new StructAsTreeNode(b, c));

                TokenNode node = TokenNode(new TokenNodeBase);
                node->node = node1;

                StructAsTreeNode node2(node, c);

                if (node2.Valid()) {
                    error = ParseNodeError("valid", "b as c as c");
                    return false;
                }
            }

            return true;
        }
    };
}
#endif