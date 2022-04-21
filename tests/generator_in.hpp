#ifndef MARTIN_TEST_GENERATOR_IN
#define MARTIN_TEST_GENERATOR_IN

#include "testing.hpp"

#include <generators/in.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_in : public Test {
    public:
        std::string GetName() const override {
            return "Generator(In)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("a in b", TreeNodeBase::Type::Misc_In, "in", true, error);
            SUBTEST_GENERATOR("a.b.c in d", TreeNodeBase::Type::Misc_In, "in", true, error);
            SUBTEST_GENERATOR("a in b.c.d", TreeNodeBase::Type::Misc_In, "in", true, error);
            SUBTEST_GENERATOR("a.b.c in d.e.f", TreeNodeBase::Type::Misc_In, "in", true, error);

            return true;
        }
    };
}
#endif