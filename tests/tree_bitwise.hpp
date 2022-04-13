#ifndef MARTIN_TEST_TREE_BITWISE
#define MARTIN_TEST_TREE_BITWISE

#include "testing.hpp"

#include <generators/bitwise.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

#define SUBTEST(str, left, right, type, valid)\
{\
    type node(left, right);\
    if (node.Valid()) {\
        if (!valid) {\
            error = ParseNodeError("valid", str);\
            return false;\
        }\
    } else if (valid) {\
        error = ParseNodeError("not valid", str);\
        return false;\
    }\
}
#define SUBTEST_SINGLE(str, left, type, valid)\
{\
    type node(left);\
    if (node.Valid()) {\
        if (!valid) {\
            error = ParseNodeError("valid", str);\
            return false;\
        }\
    } else if (valid) {\
        error = ParseNodeError("not valid", str);\
        return false;\
    }\
}

namespace Martin {
    class Test_tree_bitwise : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Bitwise)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("1 a");

            if (!ValidateTokenList(tree, error, 2)) return false;

            TokenNode one = GetTokenNodeFromTokenList(tree, 0);
            TokenNode a = GetTokenNodeFromTokenList(tree, 1);

            SUBTEST("a & 1", a, one, OPBitAndTreeNode, true);
            SUBTEST("a | 1", a, one, OPBitOrTreeNode, true);
            SUBTEST("a ^ 1", a, one, OPBitXOrTreeNode, true);
            SUBTEST_SINGLE("~a", a, OPBitNotTreeNode, true);
            SUBTEST("a << 1", a, one, OPBitShiftLeftTreeNode, true);
            SUBTEST("a >> 1", a, one, OPBitShiftRightTreeNode, true);

            return true;
        }
    };
}

#undef SUBTEST
#undef SUBTEST_SINGLE

#endif