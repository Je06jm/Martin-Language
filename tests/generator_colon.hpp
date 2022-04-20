#ifndef MARTIN_TEST_GENERATOR_COLON
#define MARTIN_TEST_GENERATOR_COLON

#include "testing.hpp"

#include <generators/colon.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_colon : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Colon)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("Int32 : b", TreeNodeBase::Type::Misc_Colon, ":", true, error);
            SUBTEST_GENERATOR("{Int32, None} : b", TreeNodeBase::Type::Misc_Colon, ":", true, error);

            return true;
        }
    };
}
#endif