#ifndef MARTIN_TEST_GENERATOR_POW
#define MARTIN_TEST_GENERATOR_POW

#include "testing.hpp"

#include <generators/pow.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_pow : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Pow)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("a ** b()", TreeNodeBase::Type::OP_Pow, "**", true, error);
            SUBTEST_GENERATOR("c ** d.e", TreeNodeBase::Type::OP_Pow, "**", true, error);

            SUBTEST_GENERATOR("(a) ** (b())", TreeNodeBase::Type::OP_Pow, "**", true, error);
            SUBTEST_GENERATOR("(c) ** (d.e)", TreeNodeBase::Type::OP_Pow, "**", true, error);

            return true;
        }
    };
}
#endif