#ifndef MARTIN_TEST_GENERATOR_FLOWCONTROLS
#define MARTIN_TEST_GENERATOR_FLOWCONTROLS

#include "testing.hpp"

#include <generators/flowcontrols.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

namespace Martin {
    class Test_generator_flowcontrols : public Test {
    public:
        std::string GetName() const override {
            return "Generator(FlowControls)";
        }

        bool RunTest() override {
            SUBTEST_GENERATOR("if (true) {let a : Int32 = 3}", TreeNodeBase::Type::FlowControl_If, "if", true, error);
            SUBTEST_GENERATOR("elif (true) {let a : Int32 = 3}", TreeNodeBase::Type::FlowControl_Elif, "elif", true, error);
            SUBTEST_GENERATOR("else {let a : Int32 = 3}", TreeNodeBase::Type::FlowControl_Else, "else", true, error);
            SUBTEST_GENERATOR("while (true) {let a : Int32 = 3}", TreeNodeBase::Type::FlowControl_While, "while", true, error);
            SUBTEST_GENERATOR("for (let a : Int32 = 0, a < 4, a += 1) {let a : Int32 = 3}", TreeNodeBase::Type::FlowControl_For, "for", true, error);
            SUBTEST_GENERATOR("for (a < 4, a += 1) {let a : Int32 = 3}", TreeNodeBase::Type::FlowControl_For, "for", true, error);
            SUBTEST_GENERATOR("foreach (let a : Any in b) {let a : Int32 = 3}", TreeNodeBase::Type::FlowControl_Foreach, "foreach", true, error);
            SUBTEST_GENERATOR("match (a) {Int32: a Float32: lambda() -> None {}}", TreeNodeBase::Type::FlowControl_Match, "match", true, error);
            SUBTEST_GENERATOR("switch (a) {IS_A: {Print(a) break} default: {Print(b) return None}}", TreeNodeBase::Type::FlowControl_Switch, "switch", true, error);
            SUBTEST_GENERATOR("return false", TreeNodeBase::Type::FlowControl_Return, "return", true, error);

            return true;
        }
    };
}
#endif