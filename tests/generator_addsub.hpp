#ifndef MARTIN_TEST_GENERATOR_ADDSUB
#define MARTIN_TEST_GENERATOR_ADDSUB

#include "testing.hpp"

#include <generators/addsub.hpp>

#include <parse.hpp>

#include "helpers/validatetree.hpp"

namespace Martin {
    class Test_generator_addsub : public Test {
    public:
        std::string GetName() const override {
            return "Generator(AddSub)";
        }

        bool RunTest() override {
            {
                auto tree = ParserSingleton.ParseString("1 + 2", error);
                
                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = (*tree)[0];
                if (node->is_token) {
                    error = "Parser node is a token when given \"1 + 2\"";
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::OP_Add) {
                    error = "Parser node is not AccessArray when given \"1 + 2\"";
                    return false;
                }

                if (!node->node->Valid()) {
                    error = "Parser node is not valid when given \"1 + 2\"";
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("1.0 + a", error);
                
                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = (*tree)[0];
                if (node->is_token) {
                    error = "Parser node is a token when given \"1.0 + a\"";
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::OP_Add) {
                    error = "Parser node is not Add when given \"1.0 + a\"";
                    return false;
                }

                if (!node->node->Valid()) {
                    error = "Parser node is not valid when given \"1.0 + a\"";
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("1 - 2", error);
                
                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = (*tree)[0];
                if (node->is_token) {
                    error = "Parser node is a token when given \"1 - 2\"";
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::OP_Sub) {
                    error = "Parser node is not Sub when given \"1 - 2\"";
                    return false;
                }

                if (!node->node->Valid()) {
                    error = "Parser node is not valid when given \"1 - 2\"";
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("1.0 - a", error);
                
                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = (*tree)[0];
                if (node->is_token) {
                    error = "Parser node is a token when given \"1.0 - a\"";
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::OP_Sub) {
                    error = "Parser node is not Sub when given \"1.0 - a\"";
                    return false;
                }

                if (!node->node->Valid()) {
                    error = "Parser node is not valid when given \"1.0 - a\"";
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("1 + 2 - 3", error);
                
                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = (*tree)[0];
                if (node->is_token) {
                    error = "Parser node is a token when given \"1 + 2 - 3\"";
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::OP_Sub) {
                    error = "Parser node is not Sub when given \"1 + 2 - 3\"";
                    return false;
                }

                if (!node->node->Valid()) {
                    error = "Parser node is not valid when given \"1 + 2 - 3\"";
                    return false;
                }
            }

            {
                auto tree = ParserSingleton.ParseString("1.0 + a - 3", error);
                
                if (!ValidateParserTree(tree, error, 1)) return false;

                TokenNode node = (*tree)[0];
                if (node->is_token) {
                    error = "Parser node is a token when given \"1.0 + a - 3\"";
                    return false;
                }

                if (node->node->GetType() != TreeNodeBase::Type::OP_Sub) {
                    error = "Parser node is not Sub when given \"1.0 + a - 3\"";
                    return false;
                }

                if (!node->node->Valid()) {
                    error = "Parser node is not valid when given \"1.0 + a - 3\"";
                    return false;
                }
            }

            return true;
        }
    };
}
#endif