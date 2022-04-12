#ifndef MARTIN_TEST_GENERATOR_ASSIGNMENTS
#define MARTIN_TEST_GENERATOR_ASSIGNMENTS

#include "testing.hpp"

#include <generators/assignments.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

#define SUBTEST(str, type, type_str, valid, error)\
{\
    auto tree = ParserSingleton.ParseString(str, error);\
    if (!ValidateParserTree(tree, error, 1)) return false;\
    if (!ValidateTreeNode(tree, 0, type, type_str, valid, str, error)) return false;\
}

namespace Martin {
    class Test_generator_assignments : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Assignments)";
        }

        bool RunTest() override {
            SUBTEST("a = 1", TreeNodeBase::Type::Assignment_Assign, "=", true, error);
            SUBTEST("a := 1", TreeNodeBase::Type::Assignment_TypeAssign, ":=", true, error);
            SUBTEST("a += 1", TreeNodeBase::Type::Assignment_AddAssign, "+=", true, error);
            SUBTEST("a -= 1", TreeNodeBase::Type::Assignment_SubAssign, "-=", true, error);
            SUBTEST("a *= 1", TreeNodeBase::Type::Assignment_MulAssign, "*=", true, error);
            SUBTEST("a /= 1", TreeNodeBase::Type::Assignment_DivAssign, "/=", true, error);
            SUBTEST("a %= 1", TreeNodeBase::Type::Assignment_ModAssign, "%=", true, error);
            SUBTEST("a **= 1", TreeNodeBase::Type::Assignment_PowAssign, "**=", true, error);
            SUBTEST("a &= 1", TreeNodeBase::Type::Assignment_BitAndAssign, "&=", true, error);
            SUBTEST("a |= 1", TreeNodeBase::Type::Assignment_BitOrAssign, "|=", true, error);
            SUBTEST("a ^= 1", TreeNodeBase::Type::Assignment_BitXOrAssign, "^=", true, error);
            SUBTEST("a ~= 1", TreeNodeBase::Type::Assignment_BitNotAssign, "~=", true, error);
            SUBTEST("a <<= 1", TreeNodeBase::Type::Assignment_BitShiftLeftAssign, "<<=", true, error);
            SUBTEST("a >>= 1", TreeNodeBase::Type::Assignment_BitShiftRightAssign, ">>=", true, error);

            return true;
        }
    };
}

#undef SUBTEST

#endif