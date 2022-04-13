#ifndef MARTIN_TEST_GENERATOR_CALL
#define MARTIN_TEST_GENERATOR_CALL

#include "testing.hpp"

#include <generators/call.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

#define SUBTEST(str, type, type_str, valid, error)\
{\
    auto tree = ParserSingleton.ParseString(str, error);\
    if (!ValidateParserTree(tree, error, 1)) return false;\
    if (!ValidateTreeNode(tree, 0, type, type_str, valid, str, error)) return false;\
}

namespace Martin {
    class Test_generator_call : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Call)";
        }

        bool RunTest() override {
            SUBTEST("a(b)", TreeNodeBase::Type::Misc_Call, "a(b)", true, error);

            return true;
        }
    };
}

#undef SUBTEST

#endif