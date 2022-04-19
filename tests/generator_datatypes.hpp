#ifndef MARTIN_TEST_GENERATOR_DATATYPES
#define MARTIN_TEST_GENERATOR_DATATYPES

#include "testing.hpp"

#include <generators/datatypes.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_datatypes : public Test {
    public:
        std::string GetName() const override {
            return "Generator(DataTypes)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("struct name { let a : Int32 let b : Float32 }", TreeNodeBase::Type::Definition_Struct, "struct", true, error);
            SUBTEST_GENERATOR("union name { let a : Int32 let b : Float32 }", TreeNodeBase::Type::Definition_Union, "union", true, error);
            SUBTEST_GENERATOR("enum name { SINGLE FLOAT }", TreeNodeBase::Type::Definition_Enum, "enum", true, error);

            return true;
        }
    };
}
#endif