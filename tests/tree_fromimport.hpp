#ifndef MARTIN_TEST_TREE_FROMIMPORT
#define MARTIN_TEST_TREE_FROMIMPORT

#include "testing.hpp"

#include <generators/fromimport.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_fromimport : public Test {
    public:
        std::string GetName() const override {
            return "Tree(FromImport)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("a b");

            if (!ValidateTokenList(tree, error, 2)) return false;

            TokenNode a = GetTokenNodeFromTokenList(tree, 0);
            TokenNode b = GetTokenNodeFromTokenList(tree, 1);

            auto tree2 = TokenizerSingleton.TokenizeString("c d");

            if (!ValidateTokenList(tree2, error, 2)) return false;

            TokenNode c = GetTokenNodeFromTokenList(tree2, 0);
            TokenNode d = GetTokenNodeFromTokenList(tree2, 1);

            std::vector<TokenNode> ids, imports;
            ids.push_back(a);

            SUBTEST_TREE("import a", ids, imports, MiscFromImportTreeNode, true);
            
            imports.push_back(c);

            SUBTEST_TREE("from a import c", ids, imports, MiscFromImportTreeNode, true);

            ids.push_back(b);
            imports.clear();

            SUBTEST_TREE("import a, b", ids, imports, MiscFromImportTreeNode, true);

            ids.clear();
            ids.push_back(a);
            imports.push_back(c);
            imports.push_back(d);

            SUBTEST_TREE("from a import c, d", ids, imports, MiscFromImportTreeNode, true);

            ids.push_back(b);

            SUBTEST_TREE("from a, b import c, d", ids, imports, MiscFromImportTreeNode, false);

            return true;
        }
    };
}
#endif