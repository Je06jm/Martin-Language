#ifndef MARTIN_TEST_GENERATOR_ENCLOSURES
#define MARTIN_TEST_GENERATOR_ENCLOSURES

#include "testing.hpp"

#include <generators/enclosures.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_enclosures : public Test {
    public:
        std::string GetName() const override {
            return "Generators(Enclosures)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("(a, b)", TreeNodeBase::Type::Struct_Parentheses, "()", true, error);
            SUBTEST_GENERATOR("{a, b}", TreeNodeBase::Type::Struct_Curly, "{}", true, error);
            SUBTEST_GENERATOR("[a, b]", TreeNodeBase::Type::Struct_Bracket, "[]", true, error);

            return true;
        }
    };
}
#endif