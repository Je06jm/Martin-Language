#ifndef MARTIN_TEST_GENERATOR_CLASS
#define MARTIN_TEST_GENERATOR_CLASS

#include "testing.hpp"

#include <generators/class.hpp>

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
    class Test_generator_class : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Class)";
        }

        bool RunTest() override {
            SUBTEST("class a {}", TreeNodeBase::Type::Misc_Class, "class", true, error);
            SUBTEST("class a : public b {}", TreeNodeBase::Type::Misc_Class, "class", true, error);
            SUBTEST("class a : public b, private c {}", TreeNodeBase::Type::Misc_Class, "class", true, error);

            return true;
        }
    };
}

#undef SUBTEST

#endif