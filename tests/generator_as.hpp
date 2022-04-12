#ifndef MARTIN_TEST_GENERATOR_AS
#define MARTIN_TEST_GENERATOR_AS

#include "testing.hpp"

#include <generators/as.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_generator_as : public Test {
    public:
        std::string GetName() const override {
            return "Generator(As)";
        }

        bool RunTest() override {
            {
                auto tree = ParserSingleton.ParseString("a as b", error);

                if (!ValidateParserTree(tree, error, 1)) return false;

                if (!ValidateTreeNode(tree, 0, TreeNodeBase::Type::Struct_As, "As", true, "a as b", error)) return false;
            }

            {
                auto tree = ParserSingleton.ParseString("1 as b", error);

                if (!ValidateParserTree(tree, error, 1)) return false;

                if (!ValidateTreeNode(tree, 0, TreeNodeBase::Type::Struct_As, "As", false, "1 as b", error)) return false;
            }

            {
                auto tree = ParserSingleton.ParseString("a as b as c", error);

                if (!ValidateParserTree(tree, error, 1)) return false;

                if (!ValidateTreeNode(tree, 0, TreeNodeBase::Type::Struct_As, "As", false, "a as b as c", error)) return false;
            }

            return true;
        }
    };
}
#endif