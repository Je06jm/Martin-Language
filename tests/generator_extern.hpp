#ifndef MARTIN_TEST_GENERATOR_EXTERN
#define MARTIN_TEST_GENERATOR_EXTERN

#include "testing.hpp"

#include <generators/extern.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_extern : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Extern)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("extern 'C' let a : Int32", TreeNodeBase::Type::Misc_Extern, "extern", true, error);
            SUBTEST_GENERATOR("extern C let a : Int32", TreeNodeBase::Type::Misc_Extern, "extern", false, error);
            SUBTEST_GENERATOR("extern 'C' a", TreeNodeBase::Type::Misc_Extern, "extern", false, error);

            return true;
        }
    };
}
#endif