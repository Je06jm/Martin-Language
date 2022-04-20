#ifndef MARTIN_TEST_TREE_EXTERN
#define MARTIN_TEST_TREE_EXTERN

#include "testing.hpp"

#include <generators/extern.hpp>
#include <generators/definitions.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_extern : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Extern)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("'C' a Int32");

            if (!ValidateTokenList(tree, error, 3)) return false;

            TokenNode C = GetTokenNodeFromTokenList(tree, 0);
            TokenNode a = GetTokenNodeFromTokenList(tree, 1);
            TokenNode int32 = GetTokenNodeFromTokenList(tree, 2);
            TokenNode let;

            std::vector<Token> ids;
            ids.push_back(a->token);

            {
                TreeNode node = TreeNode(new LetTreeNode(ids, int32));
                let = TokenNode(new TokenNodeBase);
                let->node = node;
            }

            SUBTEST_TREE("extern 'C' let a : Int32", C->token, let, ExternTreeNode, true);
            SUBTEST_TREE("extern a let a : Int32", a->token, let, ExternTreeNode, false);
            SUBTEST_TREE("extern 'C' a", C->token, a, ExternTreeNode, false);

            return true;
        }
    };
}
#endif