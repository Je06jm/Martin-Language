#ifndef MARTIN_TEST_TREE_DATATYPE
#define MARTIN_TEST_TREE_DATATYPE

#include "testing.hpp"

#include <generators/datatypes.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_tree_datatypes : public Test {
    public:
        std::string GetName() const override {
            return "Tree(DataTypes)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("name");

            if (!ValidateTokenList(tree, error, 1)) return false;

            TokenNode name = GetTokenNodeFromTokenList(tree, 0);
            TokenNode scope, scope2;

            {
                auto tree2 = ParserSingleton.ParseString("{let a : Int32 let b : Float32}", error);
                scope = (*tree2)[0];
            }

            {
                auto tree2 = ParserSingleton.ParseString("{SINGLE FLOAT}", error);
                scope2 = (*tree2)[0];
            }

            SUBTEST_TREE("struct name {let a : Int32 let b : Float32}", name, scope, StructTreeNode, true);
            SUBTEST_TREE("union name {let a : Int32 let b : Float32}", name, scope, UnionTreeNode, true);
            SUBTEST_TREE("enum name {SINGLE FLOAT}", name, scope2, EnumTreeNode, true);

            return true;
        }
    };
}
#endif