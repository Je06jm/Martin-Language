#ifndef MARTIN_TEST_GENERATOR_ACCESSTYPE
#define MARTIN_TEST_GENERATOR_ACCESSTYPE

#include "testing.hpp"

#include <generators/accesstypes.hpp>

#include <parse.hpp>

#include "helpers/validatetree.hpp"

namespace Martin {
    class Test_generator_accesstypes : public Test {
    public:
        std::string GetName() const override {
            return "Generator(AccessTypes)";
        }

        bool RunTest() override {
            {
                auto tree = ParserSingleton.ParseString("array[1] Int32", error);

                if (!ValidateParserTree(tree, error, 1, ValidateSizeType::Equals)) return false;

                TokenNode node = (*tree)[0];
                if (!node) {
                    error = "Parser node is null when given \"array[1] Int32\"";
                    return false;
                }

                if (node->is_token) {
                    error = "Parser node is a token when given \"array[1] Int32\"";
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::Access_Array) {
                    error = "Parser node is not AccessArray when given \"array[1] Int32\"";
                    return false;
                }

                if (!node->node->Valid()) {
                    error = "Parser node is not valid when given \"array[1] Int32\"";
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("array[1]", error);

                if (!tree) {
                    error = Format("Parser encountered an error when given \"array[1]\": $", error);
                    return false;
                }

                if (tree->size() == 1) {
                    error = "Parser gave one TokenNode when given \"array[1]\"";
                    return false;
                }

                TokenNode node = (*tree)[0];
                if (!node) {
                    error = "Parser node is null when given \"array[1]\"";
                    return false;
                }

                if (!node->is_token) {
                    error = "Parser node is a node when given \"array[1]\"";
                    return false;
                }
            }

            return true;
        }
    };
}
#endif