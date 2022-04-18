#ifndef MARTIN_TEST_GENERATOR_COMMA
#define MARTIN_TEST_GENERATOR_COMMA

#include "testing.hpp"

#include <generators/comma.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_comma : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Comma)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("a, true, 3.14", TreeNodeBase::Type::Struct_Comma, ",", true, error);

            return true;
        }
    };
}
#endif