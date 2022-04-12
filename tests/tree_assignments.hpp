#ifndef MARTIN_TEST_TREE_ASSIGNMENTS
#define MARTIN_TEST_TREE_ASSIGNMENTS

#include "testing.hpp"

#include <generators/assignments.hpp>

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

namespace Martin {
    class Test_tree_assignments : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Assignments)";
        }

        bool RunTest() override {
            auto tree = TokenizerSingleton.TokenizeString("1 a =");

            if (!ValidateTokenList(tree, error, 3)) return false;

            TokenNode one = GetTokenNodeFromTokenList(tree, 0);
            TokenNode a = GetTokenNodeFromTokenList(tree, 1);
            TokenNode equals = GetTokenNodeFromTokenList(tree, 2);

            SUBTEST("a = 1", a, one, AssignTreeNode, true);
            SUBTEST("a := 1", a, one, TypeAssignTreeNode, true);
            SUBTEST("a += 1", a, one, AddAssignTreeNode, true);
            SUBTEST("a -= 1", a, one, SubAssignTreeNode, true);
            SUBTEST("a *= 1", a, one, MulAssignTreeNode, true);
            SUBTEST("a /= 1", a, one, DivAssignTreeNode, true);
            SUBTEST("a %= 1", a, one, ModAssignTreeNode, true);
            SUBTEST("a **= 1", a, one, PowAssignTreeNode, true);
            SUBTEST("a &= 1", a, one, BitAndAssignTreeNode, true);
            SUBTEST("a |= 1", a, one, BitOrAssignTreeNode, true);
            SUBTEST("a ^= 1", a, one, BitXOrAssignTreeNode, true);
            SUBTEST("a ~= 1", a, one, BitNotAssignTreeNode, true);
            SUBTEST("a <<= 1", a, one, BitShiftLeftAssignTreeNode, true);
            SUBTEST("a >>= 1", a, one, BitShiftRightAssignTreeNode, true);

            SUBTEST("a = =", a, equals, AssignTreeNode, false);
            SUBTEST("a := =", a, equals, TypeAssignTreeNode, false);
            SUBTEST("a += =", a, equals, AddAssignTreeNode, false);
            SUBTEST("a -= =", a, equals, SubAssignTreeNode, false);
            SUBTEST("a *= =", a, equals, MulAssignTreeNode, false);
            SUBTEST("a /= =", a, equals, DivAssignTreeNode, false);
            SUBTEST("a %= =", a, equals, ModAssignTreeNode, false);
            SUBTEST("a **= =", a, equals, PowAssignTreeNode, false);
            SUBTEST("a &= =", a, equals, BitAndAssignTreeNode, false);
            SUBTEST("a |= =", a, equals, BitOrAssignTreeNode, false);
            SUBTEST("a ^= =", a, equals, BitXOrAssignTreeNode, false);
            SUBTEST("a ~= =", a, equals, BitNotAssignTreeNode, false);
            SUBTEST("a <<= =", a, equals, BitShiftLeftAssignTreeNode, false);
            SUBTEST("a >>= =", a, equals, BitShiftRightAssignTreeNode, false);

            SUBTEST("1 = a", one, a, AssignTreeNode, false);
            SUBTEST("1 := a", one, a, TypeAssignTreeNode, false);
            SUBTEST("1 += a", one, a, AddAssignTreeNode, false);
            SUBTEST("1 -= a", one, a, SubAssignTreeNode, false);
            SUBTEST("1 *= a", one, a, MulAssignTreeNode, false);
            SUBTEST("1 /= a", one, a, DivAssignTreeNode, false);
            SUBTEST("1 %= a", one, a, ModAssignTreeNode, false);
            SUBTEST("1 **= a", one, a, PowAssignTreeNode, false);
            SUBTEST("1 &= a", one, a, BitAndAssignTreeNode, false);
            SUBTEST("1 |= a", one, a, BitOrAssignTreeNode, false);
            SUBTEST("1 ^= a", one, a, BitXOrAssignTreeNode, false);
            SUBTEST("1 ~= a", one, a, BitNotAssignTreeNode, false);
            SUBTEST("1 <<= a", one, a, BitShiftLeftAssignTreeNode, false);
            SUBTEST("1 >>= a", one, a, BitShiftRightAssignTreeNode, false);

            return true;
        }
    };
}

#undef SUBTEST

#endif