#ifndef MARTIN_TEST_GENERATOR_DEFINITIONS
#define MARTIN_TEST_GENERATOR_DEFINITIONS

#include "testing.hpp"

#include <generators/definitions.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_definitions : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Definitions)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("let a : Int32", TreeNodeBase::Type::Definition_Let, "let", true, error);
            SUBTEST_GENERATOR("set a : Int32", TreeNodeBase::Type::Definition_Set, "set", true, error);
            SUBTEST_GENERATOR("const a : Int32", TreeNodeBase::Type::Definition_Const, "const", true, error);
            SUBTEST_GENERATOR("constexpr a : Int32", TreeNodeBase::Type::Definition_Constexpr, "constexpr", true, error);

            SUBTEST_GENERATOR("let a : {Int32, Float32}", TreeNodeBase::Type::Definition_Let, "let", true, error);
            SUBTEST_GENERATOR("set a : {Int32, Float32}", TreeNodeBase::Type::Definition_Set, "set", true, error);
            SUBTEST_GENERATOR("const a : {Int32, Float32}", TreeNodeBase::Type::Definition_Const, "const", true, error);
            SUBTEST_GENERATOR("constexpr a : {Int32, Float32}", TreeNodeBase::Type::Definition_Constexpr, "constexpr", true, error);

            return true;
        }
    };
}
#endif