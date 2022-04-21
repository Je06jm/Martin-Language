#ifndef MARTIN_TEST_GENERATOR_MULDIVMOD
#define MARTIN_TEST_GENERATOR_MULDIVMOD

#include "testing.hpp"

#include <generators/muldivmod.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_muldivmod : public Test {
    public:
        std::string GetName() const override {
            return "Generator(MulDivMod)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("a * b()", TreeNodeBase::Type::OP_Mul, "*", true, error);
            SUBTEST_GENERATOR("c * d.e", TreeNodeBase::Type::OP_Mul, "*", true, error);

            SUBTEST_GENERATOR("a / b()", TreeNodeBase::Type::OP_Div, "/", true, error);
            SUBTEST_GENERATOR("c / d.e", TreeNodeBase::Type::OP_Div, "/", true, error);

            SUBTEST_GENERATOR("a % b()", TreeNodeBase::Type::OP_Mod, "%", true, error);
            SUBTEST_GENERATOR("c % d.e", TreeNodeBase::Type::OP_Mod, "%", true, error);

            SUBTEST_GENERATOR("(a) * (b())", TreeNodeBase::Type::OP_Mul, "*", true, error);
            SUBTEST_GENERATOR("(c) * (d.e)", TreeNodeBase::Type::OP_Mul, "*", true, error);

            SUBTEST_GENERATOR("(a) / (b())", TreeNodeBase::Type::OP_Div, "/", true, error);
            SUBTEST_GENERATOR("(c) / (d.e)", TreeNodeBase::Type::OP_Div, "/", true, error);

            SUBTEST_GENERATOR("(a) % (b())", TreeNodeBase::Type::OP_Mod, "%", true, error);
            SUBTEST_GENERATOR("(c) % (d.e)", TreeNodeBase::Type::OP_Mod, "%", true, error);

            return true;
        }
    };
}
#endif