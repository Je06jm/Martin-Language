#ifndef MARTIN_TEST_GENERATOR_LOGIC
#define MARTIN_TEST_GENERATOR_LOGIC

#include "testing.hpp"

#include <generators/logical.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_logic : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Logic)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("true and b()", TreeNodeBase::Type::OP_LogicalAnd, "and", true, error);
            SUBTEST_GENERATOR("a and b==c", TreeNodeBase::Type::OP_LogicalAnd, "and", true, error);

            SUBTEST_GENERATOR("true or b()", TreeNodeBase::Type::OP_LogicalOr, "or", true, error);
            SUBTEST_GENERATOR("a or b==c", TreeNodeBase::Type::OP_LogicalOr, "or", true, error);

            SUBTEST_GENERATOR("not true", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);
            SUBTEST_GENERATOR("not b()", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);
            SUBTEST_GENERATOR("not a", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);
            SUBTEST_GENERATOR("not b==c", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);

            SUBTEST_GENERATOR("(true) and (b())", TreeNodeBase::Type::OP_LogicalAnd, "and", true, error);
            SUBTEST_GENERATOR("(a) and (b==c)", TreeNodeBase::Type::OP_LogicalAnd, "and", true, error);

            SUBTEST_GENERATOR("(true) or (b())", TreeNodeBase::Type::OP_LogicalOr, "or", true, error);
            SUBTEST_GENERATOR("(a) or (b==c)", TreeNodeBase::Type::OP_LogicalOr, "or", true, error);

            SUBTEST_GENERATOR("not (true)", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);
            SUBTEST_GENERATOR("not (b())", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);
            SUBTEST_GENERATOR("not (a)", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);
            SUBTEST_GENERATOR("not (b==c)", TreeNodeBase::Type::OP_LogicalNot, "not", true, error);

            return true;
        }
    };
}
#endif