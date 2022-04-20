#ifndef MARTIN_TEST_GENERATOR_DOT
#define MARTIN_TEST_GENERATOR_DOT

#include "testing.hpp"

#include <generators/dot.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_dot : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Dot)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("a.b", TreeNodeBase::Type::OP_Dot, ".", true, error);
            SUBTEST_GENERATOR("a.b.c", TreeNodeBase::Type::OP_Dot, ".", true, error);
            SUBTEST_GENERATOR("a.b()", TreeNodeBase::Type::OP_Dot, ".", true, error);

            return true;
        }
    };
}
#endif