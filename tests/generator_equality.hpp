#ifndef MARTIN_TEST_GENERATOR_EQUALITY
#define MARTIN_TEST_GENERATOR_EQUALITY

#include "testing.hpp"

#include <generators/equality.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_equality : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Equality)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("a == true", TreeNodeBase::Type::OP_Equals, "==", true, error);
            SUBTEST_GENERATOR("a != true", TreeNodeBase::Type::OP_NotEquals, "!=", true, error);
            SUBTEST_GENERATOR("a < 3", TreeNodeBase::Type::OP_LessThan, "<", true, error);
            SUBTEST_GENERATOR("a > 3", TreeNodeBase::Type::OP_GreaterThan, ">", true, error);
            SUBTEST_GENERATOR("a <= 3", TreeNodeBase::Type::OP_LessThanEquals, "<=", true, error);
            SUBTEST_GENERATOR("a >= 3", TreeNodeBase::Type::OP_GreaterThanEquals, ">=", true, error);

            return true;
        }
    };
}
#endif