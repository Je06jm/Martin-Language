#ifndef MARTIN_TEST_GENERATOR_CLASSACCESS
#define MARTIN_TEST_GENERATOR_CLASSACCESS

#include "testing.hpp"

#include <generators/classaccess.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_classaccess : public Test {
    public:
        std::string GetName() const override {
            return "Generator(ClassAccess)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("public wow", TreeNodeBase::Type::ClassAccess_Public, "public", true, error);
            SUBTEST_GENERATOR("private wow", TreeNodeBase::Type::ClassAccess_Private, "private", true, error);
            SUBTEST_GENERATOR("protected wow", TreeNodeBase::Type::ClassAccess_Protected, "protected", true, error);
            SUBTEST_GENERATOR("friend wow", TreeNodeBase::Type::ClassAccess_Friend, "friend", true, error);

            SUBTEST_GENERATOR("public private", TreeNodeBase::Type::ClassAccess_Public, "public", false, error);
            SUBTEST_GENERATOR("private protected", TreeNodeBase::Type::ClassAccess_Private, "private", false, error);
            SUBTEST_GENERATOR("protected friend", TreeNodeBase::Type::ClassAccess_Protected, "protected", false, error);
            SUBTEST_GENERATOR("friend public", TreeNodeBase::Type::ClassAccess_Friend, "friend", false, error);
            
            return true;
        }
    };
}

#endif