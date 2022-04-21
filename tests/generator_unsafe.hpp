#ifndef MARTIN_TEST_GENERATOR_UNSAFE
#define MARTIN_TEST_GENERATOR_UNSAFE

#include "testing.hpp"

#include <generators/unsafe.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_unsafe : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Unsafe)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("unsafe let a : Int32", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe set a : Int32", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe const a : Int32", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe constexpr a : Int32", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            
            SUBTEST_GENERATOR("unsafe let a : Int32 = 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe set a : Int32 = 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe const a : Int32 = 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe constexpr a : Int32 = 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);

            SUBTEST_GENERATOR("unsafe let a := 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe set a := 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe const a := 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);
            SUBTEST_GENERATOR("unsafe constexpr a := 0", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);

            SUBTEST_GENERATOR("unsafe func my() -> None {}", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);

            SUBTEST_GENERATOR("unsafe {}", TreeNodeBase::Type::Misc_Unsafe, "unsafe", true, error);

            return true;
        }
    };
}
#endif