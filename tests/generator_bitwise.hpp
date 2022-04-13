#ifndef MARTIN_TEST_GENERATOR_BITWISE
#define MARTIN_TEST_GENERATOR_BITWISE

#include "testing.hpp"

#include <generators/bitwise.hpp>

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
    class Test_generator_bitwise : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Bitwise)";
        }

        bool RunTest() override {
            SUBTEST("a & 1", TreeNodeBase::Type::OP_BitAnd, "&", true, error);
            SUBTEST("a | 1", TreeNodeBase::Type::OP_BitOr, "|", true, error);
            SUBTEST("a ^ 1", TreeNodeBase::Type::OP_BitXOr, "^", true, error);
            SUBTEST("~a", TreeNodeBase::Type::OP_BitNot, "~", true, error);
            SUBTEST("a << 1", TreeNodeBase::Type::OP_BitShiftLeft, "<<", true, error);
            SUBTEST("a >> 1", TreeNodeBase::Type::OP_BitShiftRight, ">>", true, error);

            return true;
        }
    };
}

#undef SUBTEST

#endif