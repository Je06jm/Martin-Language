#ifndef MARTIN_TEST_GENERATOR_CLASSTYPE
#define MARTIN_TEST_GENERATOR_CLASSTYPE

#include "testing.hpp"

#include <generators/classtype.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_classtype : public Test {
    public:
        std::string GetName() const override {
            return "Generator(ClassType)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("virtual let a : Int32", TreeNodeBase::Type::ClassType_Virtual, "virtual", true, error);
            SUBTEST_GENERATOR("override let a : Int32", TreeNodeBase::Type::ClassType_Override, "override", true, error);
            SUBTEST_GENERATOR("static let a : Int32", TreeNodeBase::Type::ClassType_Static, "static", true, error);

            SUBTEST_GENERATOR("virtual override let a : Int32", TreeNodeBase::Type::ClassType_Virtual, "virtual", true, error);
            SUBTEST_GENERATOR("override static let a : Int32", TreeNodeBase::Type::ClassType_Override, "override", true, error);
            SUBTEST_GENERATOR("static virtual let a : Int32", TreeNodeBase::Type::ClassType_Static, "static", true, error);

            return true;
        }
    };
}
#endif