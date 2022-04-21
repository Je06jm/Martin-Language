#ifndef MARTIN_TEST_TREE_UNSAFE
#define MARTIN_TEST_TREE_UNSAFE

#include "testing.hpp"

#include <generators/unsafe.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"
#include "helpers/subtests.hpp"

#define SUBTEST_CUSTOM(name, str) {\
    auto tree = ParserSingleton.ParseString(str, error);\
    if (!ValidateParserTree(tree, error, 1)) return false;\
    TokenNode token_node = GetTokenNodeFromParseList(tree, 0);\
    SUBTEST_TREE_SINGLE(name, token_node, UnsafeTreeNode, true);\
}

namespace Martin {
    class Test_tree_unsafe : public Test {
    public:
        std::string GetName() const override {
            return "Tree(Unsafe)";
        }

        bool RunTest() override {
            SUBTEST_CUSTOM("unsafe let a : Int32", "let a : Int32");
            SUBTEST_CUSTOM("unsafe set a : Int32", "set a : Int32");
            SUBTEST_CUSTOM("unsafe const a : Int32", "const a : Int32");
            SUBTEST_CUSTOM("unsafe constexpr a : Int32", "constexpr a : Int32");
            
            SUBTEST_CUSTOM("unsafe let a : Int32 = 0", "let a : Int32 = 0");
            SUBTEST_CUSTOM("unsafe set a : Int32 = 0", "set a : Int32 = 0");
            SUBTEST_CUSTOM("unsafe const a : Int32 = 0", "const a : Int32 = 0");
            SUBTEST_CUSTOM("unsafe constexpr a : Int32 = 0", "constexpr a : Int32 = 0");

            SUBTEST_CUSTOM("unsafe let a := 0", "let a := 0");
            SUBTEST_CUSTOM("unsafe set a := 0", "set a := 0");
            SUBTEST_CUSTOM("unsafe const a := 0", "const a := 0");
            SUBTEST_CUSTOM("unsafe constexpr a := 0", "constexpr a := 0");

            SUBTEST_CUSTOM("unsafe func my() -> None {}", "func my() -> None {}");

            SUBTEST_CUSTOM("unsafe {}", "{}");

            return true;
        }
    };
}

#undef SUBTEST_CUSTOM

#endif