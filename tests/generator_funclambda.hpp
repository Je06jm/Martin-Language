#ifndef MARTIN_TEST_GENERATOR_FUNCLAMBDA
#define MARTIN_TEST_GENERATOR_FUNCLAMBDA

#include "testing.hpp"

#include <generators/funclambda.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_funclambda : public Test {
    public:
        std::string GetName() const override {
            return "Generator(FuncLambda)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("func hello() -> None {}", TreeNodeBase::Type::Misc_Func, "func", true, error);
            SUBTEST_GENERATOR("func hello(let a := 3) -> None {}", TreeNodeBase::Type::Misc_Func, "func", true, error);
            SUBTEST_GENERATOR("func hello() -> {None, Int32} {}", TreeNodeBase::Type::Misc_Func, "func", true, error);
            SUBTEST_GENERATOR("func hello() -> {None, const Int32} {}", TreeNodeBase::Type::Misc_Func, "func", true, error);

            return true;
        }
    };
}
#endif