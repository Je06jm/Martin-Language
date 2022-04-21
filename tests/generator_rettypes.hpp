#ifndef MARTIN_TEST_GENERATOR_RETTYPES
#define MARTIN_TEST_GENERATOR_RETTYPES

#include "testing.hpp"

#include <generators/rettypes.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_rettypes : public Test {
    public:
        std::string GetName() const override {
            return "Generator(RetTypes)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("let a", TreeNodeBase::Type::ReturnType_Let, "let", true, error);
            SUBTEST_GENERATOR("set a", TreeNodeBase::Type::ReturnType_Set, "set", true, error);
            SUBTEST_GENERATOR("const a", TreeNodeBase::Type::ReturnType_Const, "const", true, error);
            SUBTEST_GENERATOR("constexpr a", TreeNodeBase::Type::ReturnType_Constexpr, "constexpr", true, error);

            return true;
        }
    };
}
#endif