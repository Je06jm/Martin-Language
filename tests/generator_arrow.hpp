#ifndef MARTIN_TEST_GENERATOR_ARROW
#define MARTIN_TEST_GENERATOR_ARROW

#include "testing.hpp"

#include <generators/arrow.hpp>

#include <parse.hpp>

#include "helpers/validatetree.hpp"
#include "helpers/tokennode.hpp"
#include "helpers/parseerror.hpp"

namespace Martin {
    class Test_generator_arrow : public Test {
    public:
        std::string GetName() const override {
            return "Generator(Arrow)";
        }

        bool RunTest() override {
            {
                auto tree = ParserSingleton.ParseString("() -> Int32", error);

                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = GetTokenNodeFromParseList(tree, 0);
                if (!node) {
                    error = ParseNodeError("null", "() -> Int32");
                    return false;
                }

                if (node->is_token) {
                    error = ParseNodeError("token", "() -> Int32");
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::Misc_Arrow) {
                    error = ParseNodeError("not Arrow", "() -> Int32");
                    return false;
                }

                if (!node->node->Valid()) {
                    error = ParseNodeError("not valid", "() -> Int32");
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("Float32 -> Int32", error);

                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = GetTokenNodeFromParseList(tree, 0);
                if (!node) {
                    error = ParseNodeError("null", "Float32 -> Int32");
                    return false;
                }

                if (node->is_token) {
                    error = ParseNodeError("token", "Float32 -> Int32");
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::Misc_Arrow) {
                    error = ParseNodeError("not Arrow", "Float32 -> Int32");
                    return false;
                }

                if (node->node->Valid()) {
                    error = ParseNodeError("valid", "Float32 -> Int32");
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("() -> ()", error);

                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = GetTokenNodeFromParseList(tree, 0);
                if (!node) {
                    error = ParseNodeError("null", "() -> ()");
                    return false;
                }

                if (node->is_token) {
                    error = ParseNodeError("token", "() -> ()");
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::Misc_Arrow) {
                    error = ParseNodeError("not Arrow", "() -> ()");
                    return false;
                }

                if (node->node->Valid()) {
                    error = ParseNodeError("valid", "() -> ()");
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("Int32 -> ()", error);

                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = GetTokenNodeFromParseList(tree, 0);
                if (!node) {
                    error = ParseNodeError("null", "Int32 -> ()");
                    return false;
                }

                if (node->is_token) {
                    error = ParseNodeError("token", "Int32 -> ()");
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::Misc_Arrow) {
                    error = ParseNodeError("not Arrow", "Int32 -> ()");
                    return false;
                }

                if (node->node->Valid()) {
                    error = ParseNodeError("valid", "Int32 -> ()");
                    return false;
                }
            }

            return true;
        }
    };
}
#endif